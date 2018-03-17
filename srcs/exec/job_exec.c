/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:12:24 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/17 14:29:38 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	errno is only used for the job control part
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

int						do_fork(t_job *j, t_proc *p, t_ctx *ctx)
{
	pid_t				pid;
	int					ret;

	if ((pid = fork()) == 0)
		proc_exec(p, j->pgid, ctx, j->parent->bg);
	else if (pid < 0)
		return (print_err("fork error\n", 1));
	else
	{
		p->pid = pid;
		if (ctx->istty != 0)
		{
			if (j->pgid == 0)
				j->pgid = pid;
			if ((ret = setpgid(pid, j->pgid)) != 0 && errno != ESRCH)
				perror("setpgid do_fork");
		}
	}
	return (0);
}

void					pipe_do(t_proc *p)
{
	if (p->next != NULL)
	{
		if (pipe(p->pipe_out) < 0)
			exit_err("Pipe broken\n");	//	BETTER HANDLING NEEDED
		ft_memcpy(p->next->pipe_in, p->pipe_out, sizeof(int[2]));
	}
}

void					pipe_clear(t_proc *p)
{
	if (p->pipe_in[0] != 0)
	{
		close(p->pipe_in[0]);
		close(p->pipe_in[1]);
	}
}

static int				launch_processes(t_job *j, t_ctx *ctx, int fg)
{
	t_proc				*p;

	p = j->procs;
	while (p != NULL)
	{
		pipe_do(p);
		if (p->asmts != NULL && p->argv[0] == NULL && fg)
			prefork_assign(ctx, p->asmts);
		else if (p->argv[0] != NULL)
			prepare_fork(p, ctx);
		if (do_fork(j, p, ctx) == 1)
			return (1);
		pipe_clear(p);
		p = p->next;
	}
	return (0);
}

int						job_exec(t_job *j, t_ctx *ctx)
{
	int					exp_err;

	if (j == NULL)
		return (0);
	if (j->parent == j)
		j->command = get_command(j);
	j->status = expand_job(j, ctx, &exp_err);
	if (j->parent->bg == 0)
		ctx->fg_job = j;
	if (exp_err == 0 && launch_processes(j, ctx, j->parent->bg == 0) == 1)
		return (1);
	if (j->parent->bg == 0 && exp_err)
		return (job_donext(j, ctx));
	else if (j->parent->bg == 0)
		return (job_next(j, ctx));
	return (0);
}
