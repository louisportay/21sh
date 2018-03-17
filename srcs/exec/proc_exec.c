/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:18:11 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/17 16:59:20 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

#define ENOCMD ("Command not found")

static void					exit_err(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(1);
}

void					setup_fd(int lhs, int rhs)
{
	if (lhs != rhs)
	{
		dup2(lhs, rhs);
		close(lhs);
	}
}

void					setup_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}

void					set_pid_data(t_ctx *ctx, pid_t pgid, int fg)
{
	pid_t				pid;
	int					ret;

	pid = getpid();
	if (pgid == 0)
		pgid = pid;
	if (ctx->istty == 0)
		return ;
	if ((ret = setpgid(pid, pgid)) != 0)
		perror("setpgid - set_pid_data");
	if (fg)
	{
		if ((ret = tcsetpgrp(ctx->fd, pgid)) != 0)
			perror("tcsetpgrp - set_pid_data");
	}
}

void					proc_exec(t_proc *p, pid_t pgid, t_ctx *ctx, int fg)
{
	set_pid_data(ctx, pgid, fg);
	setup_signals();
	if (p->pipe_in[0] != -1)
	{
		if (p->pipe_in[0] != STDIN_FILENO)
		{
			dup2(p->pipe_in[0], STDIN_FILENO);
			close(p->pipe_in[0]);
		}
		if (p->pipe_in[1] != STDOUT_FILENO)
			close(p->pipe_in[1]);
	}
	if (p->pipe_out[1] != -1)
	{
		if (p->pipe_out[1] != STDOUT_FILENO)
		{
			dup2(p->pipe_out[1], STDOUT_FILENO);
			close(p->pipe_out[1]);
		}
		if (p->pipe_out[0] != STDIN_FILENO)
			close(p->pipe_out[0]);
	}
	if (do_redir(p->redirs) == -1)
	{
		dprintf(2, "Ambiguous redirection\n");
		exit(1);
	}
	if (p->argv[0] == NULL)
		exit(0);
	if (p->type == EXERR)
	{
		dprintf(STDERR_FILENO, "%s: %s: %s\n", "21sh", p->argv[0], ENOCMD);
		exit(127);
	}
	if (p->type & BUILTIN)	// And what about BU_STR ?
		exit(blt_output(p));
	execve(p->data.path, p->argv, p->env);
	exit_err("Could not exec...\n");	// NEED BETTER EXIT HANDLING, ASK LPORTAY
}
