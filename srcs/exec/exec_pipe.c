/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:45:26 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/01 13:32:40 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
#include <errno.h>

static int				print_err(char *msg, int i)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	return (i);
}

static int				fork_do(t_proc *p, int fd)
{
	pid_t				pid;

	if (p->next == NULL)
	{
		close(fd);
		if (p->status & JOB_CMP)
			exit(1);
		else
			proc_exec(p);
	}
	else if ((pid = fork()) == 0)
	{
		if (p->status & JOB_CMP)
			exit(1);
		else
			proc_exec(p);
	}
	else if (pid < 0)
		return (print_err("fork error\n", 1));
	else
	{
		p->pid = pid;
		if (write(fd, (char*)&pid, 4) == -1)
		{
			ft_dprintf(STDERR_FILENO, "Closed IPC pipe.\n");
			return (-1);
		}
	}
	return (0);
}

static void				pipe_do(t_proc *p)
{
	if (p->next != NULL)
	{
		if (pipe(p->pipe_out) < 0)
		{
			if (errno == EMFILE)
				ft_dprintf(STDERR_FILENO, "Too many descriptors are active.\n");
			else if (errno == ENFILE)
				ft_dprintf(STDERR_FILENO, "The system table is full\n");
			wrap_exit(EXIT_FAILURE, get_ctxaddr());
		}
		ft_memcpy(p->next->pipe_in, p->pipe_out, sizeof(int[2]));
	}
}

static void				pipe_clear(t_proc *p)
{
	if (p->pipe_in[0] != -1)
	{
		if (p->pipe_in[0] != STDIN_FILENO)
			close(p->pipe_in[0]);
		if (p->pipe_in[1] != STDOUT_FILENO)
			close(p->pipe_in[1]);
	}
}

int						exec_pipe(t_job *j, t_ctx *ctx, int fd)
{
	t_proc				*p;

	p = j->procs;
	while (p != NULL)
	{
		pipe_do(p);
		if (do_redir(p->redirs) == -1)
			p->status = 1 | JOB_CMP;
		if ((p->status & JOB_CMP) == 0)
		{
			if (p->asmts != NULL && p->argv[0] == NULL)
				prefork_assign(ctx, p->asmts);
			else if (p->argv[0] != NULL)
				prepare_fork(p, ctx, 1);
		}
		if (fork_do(p, fd) == 1)
			return (1);
		pipe_clear(p);
		p = p->next;
	}
	_exit(-1);
	return (0);
}
