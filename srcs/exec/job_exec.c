/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:12:24 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/07 18:26:24 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int						do_fork(t_proc *p, t_job *j, int fd[2], int fg,
								t_ctx *ctx)
{
	pid_t				pid;
	int					ret;

	if ((pid = fork()) == 0)
		proc_exec(p, j->pgid, (int[3]){fd[0], fd[1], j->stderr}, fg, ctx);
	else if (pid < 0)
	{
		ft_putstr_fd("fork error\n", STDERR_FILENO);
		return (1);
	}
	else
	{
		p->pid = pid;
		if (ctx->istty != 0)
		{
			if (j->pgid == 0)
				j->pgid = pid;
			if ((ret = setpgid(pid, j->pgid)) != 0)
			{
				dprintf(STDERR_FILENO, "pid: %d - pgid: %d\n", pid, j->pgid);
				perror("setpgid do_fork");
				dprintf(STDERR_FILENO, "No pid set in 'do_fork'\n");
			}
		}
	}
	return (0);
}

void					do_pipe(t_job *job, t_proc *p, int mypipe[2],
								int *outfile)
{
	if (p->next != NULL)
	{
		if (pipe(mypipe) < 0)
		{
			ft_putstr_fd("Pipe broken\n", STDERR_FILENO);
			exit(1);
		}
		*outfile = mypipe[1];
	}
	else
		*outfile = job->stdout;
}

void					clear_pipe(t_job *j, int *infile, int *outfile,
									int new_in)
{
	if (*infile != j->stdin)
	{
		close(*infile);
		*infile = -1;
	}
	if (*outfile != j->stdout)
	{
		close(*outfile);
		*outfile = -1;
	}
	*infile = new_in;
}

static int				launch_processes(t_job *j, t_ctx *ctx, int fg)
{
	t_proc				*p;
	int					mypipe[2];
	int					infile;
	int					outfile;

	mypipe[0] = j->stdin;
	mypipe[1] = j->stdout;
	infile = j->stdin;
	outfile = j->stdout;
	p = j->procs;
	while (p != NULL)
	{
		do_pipe(j, p, mypipe, &outfile);
		if (p->asmts != NULL && p->argv[0] == NULL && fg)
			prefork_assign(ctx, p->asmts);
		else if (p->argv[0] != NULL)
			prepare_fork(p, ctx);
		if (do_fork(p, j, (int[]){infile, outfile}, fg, ctx) == 1)
			return (1);
		clear_pipe(j, &infile, &outfile, mypipe[0]);
		p = p->next;
	}
	j->running = 1;
	return (0);
}

int						job_exec(t_job *j, int fg, t_ctx *ctx)
{
	int					exp_err;

	if (j == NULL)
		return (0);
	if (j->parent == j)
		j->command = get_command(j);
	j->status = expand_job(j, ctx, &exp_err);
	if (j->parent->bg == 0)
		ctx->fg_job = j;
	if (exp_err == 0)
	{
		if (launch_processes(j, ctx, fg) == 1)
			return (1);
	}
	if (fg && exp_err)
		return (job_donext(j, ctx));
	else if (fg)
		return (job_next(j, ctx));
//	PUT_BG
	return (0);
}
