/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 14:37:37 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/15 15:50:07 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void				ldojob(t_job *j, t_ctx *ctx, size_t i)
{
	t_job				*next;

	jc_updatepipe(j);
	if (j->status & JOB_CMP)
	{
		next = (j->status & 0xFF) ? j->err : j->ok;
		if (next != NULL)
		{
			ctx->bg_jobs[i] = next;
			job_exec(ctx->bg_jobs[i], ctx);
		}
		else
		{
			j->parent->status = j->parent->status & ~0xFF;
			j->parent->status |= (j->status & 0xFF) | JOB_DON;
			j->status = j->parent->status;
		}
	}
}

static void				lhandle_rem(t_ctx *ctx)
{
	pid_t				pid;
	int					status;
	t_proc				*p;
	int					i;

	while ((pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG)) > 0)
	{
		if ((i = jc_jobfind(ctx, pid, &p)) != -1)
			jc_updateproc(ctx->bg_jobs[i], p, status);
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
	lhandle_rem(ctx);
}
