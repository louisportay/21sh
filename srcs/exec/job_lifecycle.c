/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_lifecycle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:03:23 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/07 17:56:34 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_job					*job_new(t_proc *plist)
{
	t_job				*job;

	if ((job = (t_job *)ft_memalloc(sizeof(t_job))) == NULL)
		return (NULL);
	job->procs = plist;
	job->stdin = STDIN_FILENO;
	job->stdout = STDOUT_FILENO;
	job->stderr = STDERR_FILENO;
	job->parent = job;
	return (job);
}

void					job_insert(t_job **head, t_job **curr, t_job *j)
{
	if (*head == NULL)
		*head = j;
	else
		(*curr)->next = j;
	*curr = j;
}

static size_t			lgetnext(t_ctx *ctx)
{
	size_t				i;

	i = 0;
	while (i < ctx->bg_cnt)
	{
		if (ctx->bg_jobs[i] == NULL)
			return (i);
		i++;
	}
	return ((size_t)-1);
}

void					job_ctxinsert(t_job *j, t_ctx *ctx)
{
	size_t				i;
	t_job			**tmp;

	if ((i = lgetnext(ctx)) == (size_t)-1)
	{
		tmp = (t_job **)ft_pmemalloc(sizeof(t_job *) * ctx->bg_cnt * 2,
										&on_emem, NOMEM);
		i = 0;
		while (i < ctx->bg_cnt)
		{
			tmp[i] = ctx->bg_jobs[i];
			i++;
		}
		ft_memdel((void **)&ctx->bg_jobs);
		ctx->bg_jobs = tmp;
	}
	ctx->bg_jobs[i] = j;
}
