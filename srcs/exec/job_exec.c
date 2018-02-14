/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:12:24 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/14 16:26:46 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int						do_fork(t_proc *p, t_job *j, int fd[2], int fg,
								t_ctx *ctx)
{
	pid_t				pid;

	if ((pid = fork()) == 0)
	{
		printf("fd[0]: %d - fd[1]: %d\n",fd[0], fd[1]);
		proc_exec(p, j->pgid, (int[3]){fd[0], fd[1], j->stderr}, fg, ctx);
	}
	else if (pid < 0)
	{
		ft_putstr_fd("fork error\n", STDERR_FILENO);
		return (1);
	}
	else
	{
		p->pid = pid;
//		waitpid(pid, &j->status, WUNTRACED);
//		printf("launched (\033[32m%d\033[0m)", pid);
//		for (int i = 0; p->argv[i] != NULL; i++)
//			printf(" %s", p->argv[i]);
//		printf("\n");
//		if (ctx->istty != 0)
//		{
//			if (j->pgid == 0)
//				j->pgid = pid;
//			int ret = setpgid(pid, j->pgid);
//			if (ret != 0)
//				perror ("setpgid");
//		}
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

void					do_postloop(t_job *j, int fg, t_ctx *ctx)
{
	(void)j;
	(void)fg;
	(void)ctx;
//	printf("\033[55mdo postloop\n\033[0m");
//	if (ctx->istty == 0)
//		job_wait(j);
//	else if (fg != 0)
//		job_putfg(j, 0, ctx);
//	else
//		job_putbg(j, 0);
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
//	if (jfd[0] != j->stdin)
//		close(jfd[0]);
//	else if (jfd[1] != j->stdout)
//		close(jfd[1]);
//	jfd[0] = new_in;
}

void					astr_to_buf(char **argv, t_qbuf *buf, int last)
{
	int i = 0;
	while (argv[i] != NULL)
	{
		qbuf_add(buf, argv[i]);
		if (argv[i + 1] != NULL)
			qbuf_addc(buf, ' ');
		else
			qbuf_add(buf, last ? "" : " | ");
		i++;
	}
}

int						job_exec(t_job *j, int fg, t_ctx *ctx)
{
	t_proc				*p;
	int					mypipe[2];
	int					infile;
	int					outfile;
	t_qbuf				*buf;

	mypipe[0] = j->stdin;
	mypipe[1] = j->stdout;
	infile = j->stdin;
	outfile = j->stdout;
	p = j->procs;
	buf = qbuf_new(1 << 8);
	while (p != NULL)
	{
		do_pipe(j, p, mypipe, &outfile);
		if (do_fork(p, j, (int[]){infile, outfile}, fg, ctx) == 1)
			return (1);
		clear_pipe(j, &infile, &outfile, mypipe[0]);
		astr_to_buf(p->argv, buf, p->next == NULL);
		p = p->next;
	}
	j->command = qbuf_del(&buf);
	job_wait(j);
	job_fmtinfo(j, EXE_LCHD);
//	do_postloop(j, fg, ctx);
	return (0);
}
