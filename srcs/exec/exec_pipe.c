/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:45:26 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/29 12:47:45 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	errno is only used to prevent race condition.
*/

#include <errno.h>

static void					exit_err(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(1);
}

static int				print_err(char *msg, int i)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	return (i);
}

static int				fork_do(t_job *j, t_proc *p, t_ctx *ctx, int fd)
{
	pid_t				pid;
	int					ret;

	if (p->next == NULL)
	{
		p->pid = j->pgid;
		close(fd);
		proc_exec(p, j, ctx);
	}
	else if ((pid = fork()) == 0)
		proc_exec(p, j, ctx);
	else if (pid < 0)
		return (print_err("fork error\n", 1));
	else
	{
		p->pid = pid;
		if (write(fd, (char*)&pid, 4) == -1)
		{
			perror("write fork_do");
			return (-1);
		}
		if (ctx->istty != 0)
		{
			if ((ret = setpgid(pid, j->pgid)) != 0 && errno != ESRCH)
				perror("setpgid do_fork");
		}
	}
	return (0);
}

static void				pipe_do(t_proc *p)
{
	if (p->next != NULL)
	{
		if (pipe(p->pipe_out) < 0)
			exit_err("Pipe broken\n");	//	BETTER HANDLING NEEDED
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
		if (p->asmts != NULL && p->argv[0] == NULL && j->bg == 0)
			prefork_assign(ctx, p->asmts);
		else if (p->argv[0] != NULL)
			prepare_fork(p, ctx, 1);
		if (fork_do(j, p, ctx, fd) == 1)
			return (1);
		pipe_clear(p);
		p = p->next;
	}
	_exit(-1);
	return (0);
}
