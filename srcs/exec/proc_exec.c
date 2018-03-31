/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:18:11 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/31 11:22:26 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

#define ENOCMD ("command not found")

static void				exit_err(char *msg)
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

static void				setup_pipe(t_proc *p)
{
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
}

void					proc_exec(t_proc *p)
{
	setup_signals();
	setup_pipe(p);
	if (do_redir(p->redirs) == -1)
		exit(1);
	if (p->argv[0] == NULL)
		exit(0);
	if (p->type == EXERR)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s: %s\n", "21sh", p->argv[0], ENOCMD);
		exit(127);
	}
	if (p->type & BUILTIN)
		exit(blt_output(p));
	execve(p->data.path, p->argv, p->env);
/*
**	NEED BETTER EXIT HANDLING, ASK LPORTAY
*/
	exit_err("Could not exec...\n");
}
