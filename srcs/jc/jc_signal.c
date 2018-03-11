/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 14:37:37 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/11 11:34:32 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void				ldojob(t_job *j, t_ctx *ctx, size_t i)
{
	t_job				*next;

	jc_updatepipe(j);
	if (j->completed)
	{
		next = j->status ? j->err : j->ok;
		if (next != NULL)
		{
			ctx->bg_jobs[i] = next;
			job_exec(ctx->bg_jobs[i], ctx);
		}
		else
		{
			j->parent->status = j->status;
			j = j->parent;
			j->done = 1;
			jc_notify(j, ctx, i, 0);
		}
	}
}

void					jc_signal(int signo)
{
	t_ctx				*ctx;
	size_t				i;

	if (signo != SIGCHLD)
		return ;
	ctx = get_ctxaddr(NULL);
	if (ctx->fg_job != NULL)
		jc_updatepipe(ctx->fg_job);
	i = 0;
	while (i < ctx->bg_cnt)
	{
		if (ctx->bg_jobs[i] != NULL)
			ldojob(ctx->bg_jobs[i], ctx, i);
		i++;
	}
}
