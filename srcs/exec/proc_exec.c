/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:18:11 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/16 17:25:05 by vbastion         ###   ########.fr       */
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

void					setup_signals(void (*sig)())
{
	signal(SIGINT, sig);
	signal(SIGTSTP, sig);
	signal(SIGQUIT, sig);
	signal(SIGTTOU, sig);
	signal(SIGTTIN, sig);
	signal(SIGCHLD, sig);
}

void					*PH_GET_BUILTIN(char *name)
{
	t_hash_entry		*e;

	if ((e = ft_hashset_lookup(get_ctxaddr(NULL)->builtins, name)) != NULL)
		return (e->content);
	return (NULL);
}

void					set_pid_data(t_ctx *ctx, pid_t pgid,
										int fg)
{
	pid_t				pid;
	int					ret;

	pid = getpid();
	if (pgid == 0)
		pgid = pid;
	if ((ret = setpgid(pid, pgid)) != 0)
		dprintf(STDERR_FILENO, "Error with setpgid in set_pid_data\n");
	if (fg)
	{
		if ((ret = tcsetpgrp(ctx->fd, pgid != 0 ? pgid : getpid())) != 0)
			dprintf(STDERR_FILENO, "Error with tcsetpgrp in set_pid_data\n");
	}
}

void					proc_exec(t_proc *p, pid_t pgid, int fd[3], int fg,
									t_ctx *ctx)
{
	set_pid_data(ctx, pgid, fg);
/*
**	if (ctx->istty) IF CTX IS FG DO SIG_DFL ELSE LOOK UP DFL BEHAVIOUR
*/
	setup_signals(SIG_DFL);
	setup_fd(fd[0], STDIN_FILENO);
	setup_fd(fd[1], STDOUT_FILENO);
	setup_fd(fd[2], STDERR_FILENO);
	if (p->redirs != NULL && do_redir(p->redirs) == -1)
		exit(1);
	if (p->argv[0] == NULL)
		exit(0);
	if (p->type == EXERR)
	{
		dprintf(STDERR_FILENO, "%s: %s: %s\n", "21sh", p->argv[0], ENOCMD);
		exit(1);
	}
	if (p->type == BUILTIN)
		exit(blt_output(p));
	execve(p->data.path, p->argv, p->env);
	exit_err("Could not exec...\n");
}
