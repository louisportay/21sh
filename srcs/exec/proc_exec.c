/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:18:11 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/14 19:26:07 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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
	signal(SIGINT, 	sig);
	signal(SIGTSTP, sig);
	signal(SIGQUIT, sig);
	signal(SIGTTOU, sig);
	signal(SIGTTIN, sig);
	signal(SIGCHLD, sig);
}

void					*PH_GET_BUILTIN(char *name)
{
	(void)name;
	return (NULL);
}

char *ft_astr_cat(char **argv)
{
	t_qbuf				*buf;
	int					i;

	buf = qbuf_new(64);
	i = 0;
	while (argv[i] != NULL)
	{
		qbuf_add(buf, argv[i]);
		if (argv[i + 1] != NULL)
			qbuf_addc(buf, ' ');
		i++;
	}
	return (qbuf_del(&buf));
}

#include <errno.h>

void					set_pid_data(t_ctx *ctx, pid_t pgid,
										int fg)
{
	pid_t				pid;

	pid = getpid();
	if (pgid == 0)
		pgid = pid;
	int ret = setpgid(pid, pgid);
	if (ret != 0)
		perror("setpgid in child");
	if (fg)
	{
		int ret = tcsetpgrp(ctx->fd, pgid != 0 ? pgid : getpid());
		if (ret != 0)
			perror ("tcsetpgrp");
	}
}

void					proc_exec(t_proc *p, pid_t pgid, int fd[3], int fg,
									t_ctx *ctx)
{
	char				*path;
	int					(*builtin)();
	char				**astrenv;

	(void)pgid;
	(void)fg;
	path = NULL;
	set_pid_data(ctx, pgid, fg);
	builtin = PH_GET_BUILTIN(p->argv[0]);
	if (builtin == NULL && get_path(p->argv[0], ctx, &path) == 0)
	{
		printf("%s: %s: %s\n", "21sh", p->argv[0], "Command not found");
		exit(1);
	}
//	if (ctx->istty) IF CTX IS FG DO SIG_DFL ELSE LOOK UP DFL BEHAVIOUR
		setup_signals(SIG_DFL);
	setup_fd(fd[0], STDIN_FILENO);
	setup_fd(fd[1], STDOUT_FILENO);
	setup_fd(fd[2], STDERR_FILENO);
	if (p->redirs != NULL)
		do_redir(p->redirs);
	// LPORTAY'S REDIRECTIONS
	if ((astrenv = ft_astr_dup(ctx->environ)) == NULL)
		exit_err("Not enough memory\n"); // BIG BIG ERROR BUT MIGHT BE UNESCAPBLE
	// DO ASSIGNMENT IF NOT ONLY ASSIGNMENTS
	// IF ONLY ASSIGNMENT, ASSIGN ENV OR LOCALS THEN DO SIMPLE EXIT <- in ctx
	if (builtin != NULL)
		exit(builtin(p->argv, ctx));
	execve(path, p->argv, astrenv);
	exit_err("Could not exec...\n");
}
