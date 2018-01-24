/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:12:24 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/24 18:29:34 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int						do_fork(t_proc *p, t_job *j, int fd[2], int fg,
								int istty)
{
	pid_t				pid;

	if ((pid = fork()) == 0)
		proc_exec(p, j->pgid, (int[3]){fd[0], fd[1], j->stderr}, fg);
	else if (pid < 0)
	{
		ft_putstr_fd("fork error\n", STDERR_FILENO);
		return (1);
	}
	else
	{
		p->pid = pid;
		if (istty != 0)
		{
			if (j->pgid == 0)
				j->pgid = pid;
			setpgid(pid, j->pgid);
		}
	}
	return (0);
}

int						do_pipe(t_proc *p, int fd[2], int *outfile)
{
	if (p->next != NULL)
	{
		if (pipe(fd) < 0)
		{
			ft_putstr_fd("Pipe broken\n", STDERR_FILENO);
			return (1);
		}
		*outfile = fd[1];
	}
	return (0);
}

void					do_postloop(t_job *j, int fg, int istty)
{
	if (istty == 0)
		job_wait(j);
	else if (fg != 0)
		job_putfg(j, 0);
	else
		job_putbg(j, 0);
}

int						job_exec(t_job *j, int fg, int istty)
{
	t_proc				*p;
	int					fd[2];
	int					infile;
	int					outfile;

	infile = j->stdin;
	p = j->first_process;
	while (p != NULL)
	{
		if (do_pipe(p, fd, &outfile) == 1)
			return (1);
		if (do_fork(p, j, (int[2]){infile, outfile}, fg, istty) == 1)
			return (1);
		if (infile != j->stdin)
			close(infile);
		if (outfile != j->stdout)
			close(outfile);
		infile = fd[0];
		p = p->next;
	}
	job_fmtinfo(j, EXE_LCHD);
	do_postloop(j, fg, istty);
	return (0);
}

