/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:18:11 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/15 11:07:53 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

#define ENOCMD ("Command not found")

void					exit_err(char *msg)
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
	{
		perror("setpgid - set_pid_data");
		dprintf(STDERR_FILENO, "Error with setpgid in set_pid_data\n");
	}
	if (fg)
	{
		if ((ret = tcsetpgrp(ctx->fd, pgid != 0 ? pgid : getpid())) != 0)
		{
			perror("tcsetpgrp - set_pid_data");
			dprintf(STDERR_FILENO, "Error with tcsetpgrp in set_pid_data\n");
		}
	}
}

void					proc_exec(t_proc *p, pid_t pgid, int fd[3], int fg,
		t_ctx *ctx)
{
	set_pid_data(ctx, pgid, fg);
/*
 **	if (ctx->istty) IF CTX IS FG DO SIG_DFL ELSE LOOK UP DFL BEHAVIOUR
 */
	setup_signals();
	setup_fd(fd[0], STDIN_FILENO);
	setup_fd(fd[1], STDOUT_FILENO);
	setup_fd(fd[2], STDERR_FILENO);
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
	if (p->type & BUILTIN)
		exit(blt_output(p));
	execve(p->data.path, p->argv, p->env);
	exit_err("Could not exec...\n");
}
