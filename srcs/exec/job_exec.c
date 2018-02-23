/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:12:24 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/23 22:04:38 by vbastion         ###   ########.fr       */
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
				dprintf(STDERR_FILENO, "No pid set in 'do_fork'\n");
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

/*
**	void					do_postloop(t_job *j, int fg, t_ctx *ctx)
**	{
**		if (ctx->istty == 0)
**			job_wait(j);
**		else if (fg != 0)
**			job_putfg(j, 0, ctx);
**		else
**			job_putbg(j, 0);
**	}
*/

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

int						job_exec(t_job *j, int fg, t_ctx *ctx)
{
	t_proc				*p;
	int					mypipe[2];
	int					infile;
	int					outfile;
	t_qbuf				*buf;
	int					exp_err;

	if (j == NULL)
		return (0);
	mypipe[0] = j->stdin;
	mypipe[1] = j->stdout;
	infile = j->stdin;
	outfile = j->stdout;
	p = j->procs;
	buf = qbuf_new(2 << 8);
	if (expand_job(j, ctx, &exp_err) != 0)
		;
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
		astr_to_buf(p->argv, buf, p->next == NULL);
		p = p->next;
	}
	j->command = qbuf_del(&buf);
	if (fg)
		return (job_next(j, ctx));
	job_fmtinfo(j, EXE_LCHD);
	job_putbg(j, 0);
	return (0);
}
