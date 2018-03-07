/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 14:37:37 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/07 18:37:29 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void					jc_notify(t_job *j, int i)
{
	if (j->parent->done == 1)
		printf("[%d]%-3c%-24s%s\n", i + 1, ' ', "Done", j->parent->command);
	else
		printf("[%d]%-3c%-24s%s\n", i + 1, ' ', "Not done", j->parent->command);
}

void					jc_print(t_ctx *ctx)
{
	size_t				i;

	i = 0;
	while (i < ctx->bg_cnt)
	{
		if (ctx->bg_jobs[i] != NULL)
			jc_notify(ctx->bg_jobs[i], (int)i);
		i++;
	}
}

void					jc_signal(int signo)
{
	pid_t				pid;
	int					status;
	int					i;
	t_ctx				*ctx;
	t_job				*j;
	t_job				*next;

	if (signo != SIGCHLD)
		return ;
	ctx = get_ctxaddr(NULL);
	while ((pid = waitpid(WAIT_ANY, &status, WUNTRACED)) > 0)
	{
		if (jc_procfind(ctx->fg_job, pid) == 1)
			jc_updatepipe(ctx->fg_job);
		else if ((i = jc_jobfind(ctx, pid)) != -1)
		{
			j = ctx->bg_jobs[i];
			jc_updatepipe(j);
			if (j->completed)
			{
				next = j->status ? j->err : j->ok;
				if (next != NULL)
				{
					ctx->bg_jobs[i] = next;
					job_exec(ctx->bg_jobs[i], 0, ctx);
				}
				else
				{
					j = j->parent;
					jc_notify(j, i);
					ctx->bg_jobs[i]->parent->done = 1;
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
