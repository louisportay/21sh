/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:18:11 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/23 15:32:41 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

#define ENOCMD ("command not found")

static void					exit_err(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(1);
}

static void				setup_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}

static void				set_pid_data(t_ctx *ctx, t_job *j)
{
	pid_t				pid;
	int					ret;

	pid = getpid();
	if (j->pgid == 0)
		j->pgid = pid;
	if (ctx->istty == 0)
		return ;
	if ((ret = setpgid(pid, j->pgid)) != 0)
		perror("setpgid - set_pid_data");
	if (j->parent->bg == 0)
	{
		if ((ret = tcsetpgrp(ctx->fd, j->pgid)) != 0)
			perror("tcsetpgrp - set_pid_data");
	}
}

void					proc_exec(t_proc *p, t_job *j, t_ctx *ctx)
{
	set_pid_data(ctx, j);
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
		exit(1);
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
