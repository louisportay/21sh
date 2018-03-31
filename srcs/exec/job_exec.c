/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:12:24 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/31 11:52:02 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
#include <errno.h>

static void				lcheck(t_proc *p)
{
	int					status;

	waitpid(p->pid, &status, WUNTRACED);
	p->status = (p->status & 0xFF) | JOB_SIG | JOB_CMP;
}

static void				l_handle_proc_status(t_proc *p, int status)
{
	if (WIFEXITED(status))
		p->status = WEXITSTATUS(status) | JOB_CMP;
	else if (WIFSTOPPED(status))
	{
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGPIPE)
		{
			waitpid(p->pid, &status, WUNTRACED);
			p->status = (p->status & 0xFF) | JOB_CMP;
			return ;
		}
		p->status = WTERMSIG(status);
		lcheck(p);
	}
	else
		ft_printf("Received unhandled status\n");
}

static int				l_wait_for_job(t_job *j)
{
	t_proc				*p;
	int					status;
	pid_t				pid;

	p = j->procs;
	while (p != NULL)
	{
		while ((p->status & JOB_CMP) == 0)
		{
			pid = waitpid(p->pid, &status, WUNTRACED);
			if (pid < 0)
			{
				if (errno == ECHILD)
					;
				else
					ft_dprintf(STDERR_FILENO, "Critical pid error.\n");
			}
			l_handle_proc_status(p, status);
		}
		if (p->next == NULL)
			j->status = (p->status & 0xFF) | JOB_CMP;
		p = p->next;
	}
	return (0);
}

static int				l_job_exec_loop(t_job **job, t_ctx *ctx, int exp_err)
{
	t_job				*j;

	j = *job;
	if (exp_err)
	{
		if (j->err == NULL)
			j->parent->status = 1 | JOB_DON;
		else
			*job = j->err;
	}
	else
	{
		if (((j->procs->next != NULL) ? job_pipe(j, ctx)
							: job_one(j, ctx)) == 1)
			return (1);
		l_wait_for_job(j);
		if ((j->status & 0xFF) && j->err != NULL)
			*job = j->err;
		else if ((j->status & 0xFF) == 0 && j->ok != NULL)
			*job = j->ok;
		else
			j->parent->status = JOB_DON | (j->status & 0xFF);
	}
	return (0);
}

int						job_exec(t_job *j, t_ctx *ctx)
{
	int					exp_err;

	if (j == NULL)
		return (0);
	j->command = get_command(j);
	while ((j->parent->status & JOB_DON) == 0)
	{
		j->status = expand_job(j, ctx, &exp_err);
		if (l_job_exec_loop(&j, ctx, exp_err) == 1)
			return (1);
	}
	return (0);
}
