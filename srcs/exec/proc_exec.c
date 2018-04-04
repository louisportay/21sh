/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:18:11 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/04 20:00:52 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

#define ENOCMD ("command not found")

static void				setup_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}

void					exec_print_err(enum e_extype type, char *path)
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
	if (p->argv[0] == NULL)
	{
		proc_clear(&p);
		exit(0);
	}
	if (p->type & EXERR)
	{
		exec_print_err(p->type, p->type == EXNFOD ? p->data.path : p->argv[0]);
		proc_clear(&p);
		exit(127);
	}
	if (p->type & BUILTIN)
	{
		s = p->status & 0xFF;
		proc_clear(&p);
		exit(s);
	}
	execve(p->data.path, p->argv, p->env);
	ft_dprintf(STDERR_FILENO, "21sh: %s: Unknown command\n", p->data.path);
	exit(1);
}
