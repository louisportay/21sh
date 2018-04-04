/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:18:11 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/04 14:18:47 by lportay          ###   ########.fr       */
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

static void				lprint_err(enum e_extype type, char *path)
{
	char				*fmt;

	if (type == EXDIR)
		fmt = "21sh: %s: Is a directory\n";
	else if (type == EXPERM)
		fmt = "21sh: %s: Permission denied\n";
	else if (type == EXNFD)
		fmt = "21sh: %s: command not found\n";
	else if (type == EXNFOD)
		fmt = "21sh: %s: No such file or directory\n";
	ft_dprintf(STDERR_FILENO, fmt, path);
}

void					proc_exec(t_proc *p)
{
	int					s;

	setup_signals();
	setup_pipe(p);
	if (p->argv[0] == NULL)
	{
		proc_clear(&p);
		exit(0);
	}
	if (p->type & EXERR)
	{
		lprint_err(p->type, p->type == EXNFOD ? p->data.path : p->argv[0]);
		proc_clear(&p);
		exit(127);//leak de fork
	}
	if (p->type & BUILTIN)
	{
		s = p->status & 0xFF;
		proc_clear(&p);
		exit(s);
	}
	execve(p->data.path, p->argv, p->env);
	exit_err("Could not exec...\n");//tej ca 
}
