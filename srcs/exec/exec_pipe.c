/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:45:26 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/08 17:41:06 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
#include <errno.h>

static void				l_last_job(t_proc *p, int fd, t_ctx *ctx)
{
	close(fd);
	if (ctx->set & BU_SET_ONCMD)
		proc_print(p);
	if (p->status & JOB_CMP)
		exit(1);
	else
		proc_exec(p);
}

static int				fork_do(t_proc *p, int fd, t_ctx *ctx)
{
	pid_t				pid;

	if (p->next == NULL)
		l_last_job(p, fd, ctx);
	else if ((pid = fork()) == 0)
	{
		if (ctx->set & BU_SET_ONCMD)
			proc_print(p);
		if (p->status & JOB_CMP)
			exit(1);
		else
			proc_exec(p);
	}
	else if (pid < 0)
		return (print_err("21sh: fork: could not fork\n", 1));
	else
	{
		p->pid = pid;
		if (write(fd, (char*)&pid, sizeof(int)) == -1)
		{
			ft_dprintf(STDERR_FILENO, "Closed IPC pipe.\n");
			return (-1);
		}
	}
	return (0);
}

/*
** wowsuchnameinmuchshell
*/

static void				pipingation(t_proc *p)
{
	int					fd[2];

	if (p->pipe_in != -1)
	{
		dup2(p->pipe_in, STDIN_FILENO);
		close(p->pipe_in);
	}
	if (p->next != NULL)
	{
		if (pipe(fd) < 0)
		{
			if (errno == EMFILE)
				ft_dprintf(STDERR_FILENO, "Too many descriptors are active.\n");
			else if (errno == ENFILE)
				ft_dprintf(STDERR_FILENO, "The system table is full\n");
			wrap_exit(EXIT_FAILURE, get_ctxaddr());
		}
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		p->next->pipe_in = fd[0];
	}
	else
		dup2(get_ctxaddr()->std_fd[1], STDOUT_FILENO);
}

int						exec_pipe(t_job *j, t_ctx *ctx, int fd)
{
	t_proc				*p;

	p = j->procs;
	while (p != NULL)
	{
		pipingation(p);
		if (do_redir(p->redirs, ctx->std_fd) == -1)
			p->status = 1 | JOB_CMP;
		if ((p->status & JOB_CMP) == 0)
		{
			if (p->asmts != NULL && p->argv[0] == NULL)
				prefork_assign(ctx, p->asmts);
			else if (p->argv[0] != NULL)
				prepare_fork(p, ctx, 1);
		}
		if (fork_do(p, fd, ctx) == 1)
		{
			clear_pipe(j, p, fd);
			exit(-42);
		}
//			return (1);
		p = p->next;
	}
	exit(-1);
	return (0);
}
