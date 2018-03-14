/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:06:04 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/14 17:05:31 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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
		return (j->status = (job_exec(j->err, ctx) & 0xFF));
	return (j->status & 0xFF);
}

int						job_next(t_job *j, t_ctx *ctx)
{
	j->status = job_putfg(j, ctx) & 0xFF;
	if (j->status & JOB_STP)
		return (j->status & 0xFF);
	return (job_donext(j, ctx) & 0xFF);
}

int						job_putfg(t_job *j, t_ctx *ctx)
{
	int					ret;

	if (ctx->istty && (ret = tcsetpgrp(ctx->fd, j->pgid)) != 0)
		perror("tcsetpgrp - job_putfg");
	ctx->fg_job = j;
	signal(SIGCHLD, &jc_signal);
	while ((j->status & (JOB_STP | JOB_CMP)) == 0)
	{
		jc_updatebg(ctx);
		jc_updatepipe(j);
	}
	if (ctx->istty && (ret = tcsetpgrp(ctx->fd, ctx->pgid)) != 0)
		perror("tcsetpgrp");
	signal(SIGCHLD, SIG_IGN);
	if (j->status & JOB_STP)
		jc_addtobg(ctx, j);
	return (j->status & 0xFF);
}
