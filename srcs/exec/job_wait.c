/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:06:04 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/23 18:09:19 by vbastion         ###   ########.fr       */
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

static int				get_last_status(t_job *j)
{
	t_proc				*p;

	p = j->procs;

	if (p == NULL)
		return (0);
	while (p->next != NULL)
		p = p->next;
	return (p->status & 0xFF);
}

int						job_putfg(t_job *j, t_ctx *ctx)
{
	int					ret;

	if (ctx->istty && (ret = tcsetpgrp(ctx->fd, j->pgid)) != 0)
		perror("tcsetpgrp - job_putfg");
	ctx->fg_job = j;
	while ((j->status & (JOB_STP | JOB_CMP)) == 0)
	{
		jc_updatepipe(j);
		jc_updatebg(ctx);
	}
	j->status = get_last_status(j) | (j->status & ~0xFF);;
	if (j->status & JOB_STP)
		jc_addtobg(ctx, j);
	ctx->fg_job = NULL;
	if (ctx->istty && (ret = tcsetpgrp(ctx->fd, ctx->pgid)) != 0)
		perror("tcsetpgrp");
	return (j->status & 0xFF);
}
