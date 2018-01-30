/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:12:24 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/30 18:40:05 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int						do_fork(t_proc *p, t_job *j, int fd[2], int fg,
								t_env *env)
{
	pid_t				pid;

	if ((pid = fork()) == 0)
		proc_exec(p, j->pgid, (int[3]){fd[0], fd[1], j->stderr}, fg, env);
	else if (pid < 0)
	{
		ft_putstr_fd("fork error\n", STDERR_FILENO);
		return (1);
	}
	else
	{
		p->pid = pid;
		if (env->istty != 0)
		{
			if (j->pgid == 0)
				j->pgid = pid;
			setpgid(pid, j->pgid);
		}
	}
	return (0);
}

void					do_pipe(t_job *job, t_proc *p, int fd[2], int *outfile)
{
	if (p->next != NULL)
	{
		if (pipe(fd) < 0)
		{
			ft_putstr_fd("Pipe broken\n", STDERR_FILENO);
			exit(1);
		}
		*outfile = fd[1];
	}
	else
		*outfile = job->stdout;
}

void					do_postloop(t_job *j, int fg, t_env *env)
{
	if (env->istty == 0)
		job_wait(j);
	else if (fg != 0)
	{
		printf("fg-ing\n");
		job_putfg(j, 0, env);
	}
	else
		job_putbg(j, 0);
}

int						job_exec(t_job *j, int fg, t_env *env)
{
	t_proc				*p;
	int					fd[2];
	int					infile;
	int					outfile;

	infile = j->stdin;
	p = j->procs;
	printf("fd - 0: %d, 1: %d, 2: %d\n", j->stdin, j->stdout, j->stderr);
	t_qbuf *buf = qbuf_new(1 << 8);
	while (p != NULL)
	{
		do_pipe(j, p, fd, &outfile);
		if (do_fork(p, j, (int[2]){infile, outfile}, fg, env) == 1)
			return (1);
		if (infile != j->stdin)
			close(infile);
		if (outfile != j->stdout)
			close(outfile);
		infile = fd[0];
		int i = 0;
		while (p->argv[i] != NULL)
		{
			qbuf_add(buf, p->argv[i]);
			if (p->argv[i + 1] != NULL)
				qbuf_addc(buf, ' ');
			else
				qbuf_add(buf, p->next == NULL ? "" : " | ");
			i++;
		}
		p = p->next;
	}
	j->command = qbuf_del(&buf);
	job_fmtinfo(j, EXE_LCHD);
	do_postloop(j, fg, env);
	return (0);
}

