/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:45:26 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/21 18:55:53 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include <errno.h>

static void				open_pipe(t_proc *p, int *pipes)
{
	if (p->next != NULL)
	{
		if (pipe(pipes) < 0)
		{
			if (errno == EMFILE)
				ft_dprintf(STDERR_FILENO, "Too many descriptors are active.\n");
			else if (errno == ENFILE)
				ft_dprintf(STDERR_FILENO, "The system table is full\n");
			wrap_exit(EXIT_FAILURE, get_ctxaddr());
		}
		dup2(pipes[1], STDOUT_FILENO);
		close(pipes[1]);
		pipes[1] = -1;
	}
	else
		dup2(get_ctxaddr()->std_fd[1], STDOUT_FILENO);
}

static void				prefork(t_ctx *ctx, t_proc *p)
{
	if (p->asmts != NULL && p->argv[0] == NULL)
		prefork_assign(ctx, p->asmts);
	else if (p->argv[0] != NULL)
		prepare_fork(p, ctx, 1);
}

static void				l_setpgid(pid_t *pgid)
{
	*pgid = getpid();
	if (job_setpgid(*pgid, *pgid) == -1)
		exit(-42);
	else if (job_setpgrp(*pgid) == -1)
		exit(-42);
}

int						exec_pipe(t_job *j, t_ctx *ctx, int fd)
{
	t_proc				*p;
	int					*pipes;
	pid_t				pgid;

	l_setpgid(&pgid);
	p = j->procs;
	pipes = (int[]){-1, -1, -1, -1};
	while (p != NULL)
	{
		restore_fds(ctx);
		open_pipe(p, pipes);
		if (do_redir(p->redirs, ctx->std_fd, pipes, fd) == -1)
			p->is_err = 1;
		if ((p->status & JOB_CMP) == 0)
			prefork(ctx, p);
		if (fork_do(p, fd, pgid, pipes) == 1)
		{
			clear_pipe(j, p, fd);
			exit(-42);
		}
		p = p->next;
	}
	exit(-1);
	return (0);
}
