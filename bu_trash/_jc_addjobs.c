/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_addjobs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 18:48:24 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/26 20:13:51 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void				jc_insertjob(t_job *tmp, t_ctx *ctx, size_t *i)
{
	int					ok;
	t_job				**new_arr;

	ok = 0;
	while (*i < ctx->bg_cnt && ok == 0)
	{
		if (ctx->bg_jobs[*i] == NULL)
			ok = 1;
		else
			(*i)++;
	}
	if (ok == 0)
	{
		new_arr = (t_job **)ft_pmemalloc(sizeof(t_job *) * ctx->bg_cnt * 2,
											&on_emem, NOMEM);
		*i = 0;
		while (*i < ctx->bg_cnt)
		{
			new_arr[*i] = ctx->bg_jobs[*i];
			(*i)++;
		}
		ft_memdel((void **)&ctx->bg_jobs);
		ctx->bg_jobs = new_arr;
		ctx->bg_cnt <<= 1;
	}
	ctx->bg_jobs[*i] = tmp;
}

void					jc_addjobs(t_job *jobs, t_ctx *ctx)
{
	size_t				i;
	t_job				*tmp;

	i = 0;
	while (jobs != NULL)
	{
		tmp = jobs;
		jobs = jobs->next;
		jc_insertjob(tmp, ctx, &i);
	}
}
