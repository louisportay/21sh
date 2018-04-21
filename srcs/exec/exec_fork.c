/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 14:46:43 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/21 16:55:48 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

#define DO_DUP 1
#define DO_CLO 2
#define DO_NUL 4
#define DO_MOV 8

static void				chg_fd(int *fd, int flag, int tar, int *move)
{
	if (*fd != -1)
	{
		if (flag & DO_MOV)
			*move = *fd;
		if (flag & DO_DUP)
			dup2(*fd, tar);
		if (flag & DO_CLO)
			close(*fd);
		if (flag & DO_NUL)
			*fd = -1;
	}
}

static void				l_last_job(t_proc *p, int fd, t_ctx *ctx, int *pipes)
{
	chg_fd(pipes + 2, DO_DUP | DO_CLO, STDIN_FILENO, NULL);
	chg_fd(pipes + 3, DO_CLO, 0, NULL);
	chg_fd(pipes, DO_CLO, 0, NULL);
	chg_fd(pipes + 1, DO_CLO, 0, NULL);
	close(fd);
	dup2(ctx->std_fd[0], STDOUT_FILENO);
	if (ctx->set & BU_SET_ONCMD)
		proc_print(p);
	if (p->status & JOB_CMP)
		exit(1);
	else
		proc_exec(p);
}

static void				fork_child(t_proc *p, t_ctx *ctx, int *pipes)
{
	chg_fd(pipes + 1, DO_DUP | DO_CLO, STDOUT_FILENO, NULL);
	chg_fd(pipes, DO_CLO, 0, NULL);
	chg_fd(pipes + 2, DO_DUP | DO_CLO, STDIN_FILENO, NULL);
	chg_fd(pipes + 3, DO_CLO, 0, NULL);
	if (ctx->set & BU_SET_ONCMD)
		proc_print(p);
	if (p->status & JOB_CMP)
		exit(1);
	else
		proc_exec(p);
}

int						fork_do(t_proc *p, int fd, t_ctx *ctx, int *pipes)
{
	pid_t				pid;

	if (p->next == NULL)
		l_last_job(p, fd, ctx, pipes);
	else if ((pid = fork()) == 0)
		fork_child(p, ctx, pipes);
	else if (pid < 0)
		return (print_err("42sh: fork: could not fork\n", 1));
	else
	{
		chg_fd(pipes + 2, DO_CLO | DO_NUL, 0, NULL);
		chg_fd(pipes + 3, DO_CLO | DO_NUL, 0, NULL);
		chg_fd(pipes + 1, DO_CLO | DO_NUL, 0, NULL);
		chg_fd(pipes, DO_MOV, 0, pipes + 2);
		p->pid = pid;
		if (write(fd, (char*)&pid, sizeof(int)) == -1)
		{
			ft_dprintf(STDERR_FILENO, "Closed IPC pipe.\n");
			return (-1);
		}
	}
	return (0);
}
