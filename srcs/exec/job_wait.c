/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:06:04 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/19 19:51:12 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
#include <errno.h>

int						job_donext(t_job *j, t_ctx *ctx)
{
	int					ret;

	if ((j->status & 0xFF) == 0)
	{
		if (j->ok == NULL)
			return (j->status & 0xFF);
		else
		{
			if ((ret = job_exec(j->ok, ctx)) == 0
					&& (j->parent->status & 0xFF) == 0)
				return (j->parent->status & 0xFF);
			else
				return (job_exec(j->err, ctx) & 0xFF);

		}
	}
	if (j->err != NULL)
		return (job_exec(j->err, ctx) & 0xFF);
	return (j->status & 0xFF);
}

int						job_next(t_job *j, t_ctx *ctx)
{
	j->status = (j->status & ~0xFF) | (job_putfg(j, ctx) & 0xFF);
	if (j->status & JOB_STP)
		return (j->status & 0xFF);
	else if ((j->status & JOB_SIG) || (j->parent->status & JOB_SIG))
		return (1);
	return (job_donext(j, ctx) & 0xFF);
}

static t_proc			*job_lastproc(t_job *j)
{
	t_proc				*p;

	p = j->procs;
	while (p != NULL)
	{
		if (p->next == NULL)
			return (p);
		p = p->next;
	}
	return (NULL);
}

static pid_t			job_lastpid(t_job *j)
{
	t_proc				*p;

	if ((p = job_lastproc(j)) == NULL)
		return (-1);
	return (p->pid);
}

static t_proc			*job_findproc(t_job *j, pid_t pid)
{
	t_proc				*p;

	p = j->procs;
	while (p != NULL)
	{
		if (p->pid == pid)
			return (p);
		p = p->next;
	}
	return (NULL);
}

int						exec_waitfg(t_job *j)
{
	pid_t				pid;
	int					status;
	pid_t				last;
	t_proc				*p;

	if ((last = job_lastpid(j)) == -1)
		return (-2);
	while ((pid = waitpid(j->pgid, &status, WUNTRACED)) > -1)
	{
		if ((p = job_findproc(j, pid)) == NULL)
			return (-4);
		jc_updateproc(j, p, status);
		if (p->status & JOB_STP)
		{
			j->status = JOB_STP;
			kill(-j->pgid, SIGTSTP);
			return (0);
		}
	}
	if (errno != ECHILD)
		return (-3);
	if ((p = job_lastproc(j)) == NULL)
		return (-4);
	j->status = (p->status & 0xFF) | JOB_CMP;
	return (0);
}

int						job_putfg(t_job *j, t_ctx *ctx)
{
	int					ret;

	if (ctx->istty && (ret = tcsetpgrp(ctx->fd, j->pgid)) != 0)
		perror("tcsetpgrp - job_putfg");
	signal(SIGCHLD, &jc_signal);
	if ((ret = exec_waitfg(j)) != 0)
	{
		printf("ret: %d\n", ret);
		printf("Add real handling please!\n");	// PLS
		return (ret);
	}
	if (ctx->istty && (ret = tcsetpgrp(ctx->fd, ctx->pgid)) != 0)
		perror("tcsetpgrp");
	jc_updatebg(ctx);
//	signal(SIGCHLD, SIG_IGN);
	if (j->status & JOB_STP)
		jc_addtobg(ctx, j);
	return (j->status & 0xFF);
}
