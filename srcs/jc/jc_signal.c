/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 14:37:37 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/08 14:49:43 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void					jc_signal(int signo)
{
	pid_t				pid;
	int					status;
	int					i;
	t_ctx				*ctx;
	t_job				*j;
	t_job				*next;
	t_proc				*p;

	if (signo != SIGCHLD)
		return ;
	ctx = get_ctxaddr(NULL);
	while ((pid = waitpid(WAIT_ANY, &status, WUNTRACED)) > 0)
	{
		if (jc_procfind(ctx->fg_job, pid, &p) == 1)
		{
			jc_updateproc(ctx->fg_job, p, status);
			jc_updatepipe(ctx->fg_job);
		}
		else if ((i = jc_jobfind(ctx, pid, &p)) != -1)
		{
			j = ctx->bg_jobs[i];
			jc_updateproc(j, p, status);
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
					jc_notify(j, i, 0);
				}
			}
		}
		else
		{
			dprintf(STDERR_FILENO, "No corresponding job\n");
			return ;
		}
	}
}

void					jc_clear(t_ctx *ctx)
{
	size_t				i;

	i = 0;
	while (i < ctx->bg_cnt)
	{
		if (ctx->bg_jobs[i] != NULL && ctx->bg_jobs[i]->parent->done == 1)
		{
			job_safeclear(ctx->bg_jobs + i);
			ctx->bg_jobs[i] = NULL;
		}
		i++;
	}
}
