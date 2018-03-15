/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_addbg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 18:07:50 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/14 19:21:33 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

size_t					jc_getbgnext(t_ctx *ctx)
{
	size_t				i;

	i = 0;
	while (i < ctx->bg_cnt)
	{
		if (ctx->bg_jobs[i] == NULL)
			return (i);
		i++;
	}
	return (-1);
}

size_t					jc_bggrow(t_ctx *ctx)
{
	t_job				**arr;
	size_t				i;

	arr = (t_job **)ft_pmemalloc(sizeof(t_job *) * ctx->bg_cnt * 2,
									&on_emem, NOMEM);
	i = 0;
	while (i < ctx->bg_cnt)
	{
		arr[i] = ctx->bg_jobs[i];
		i++;
	}
	ft_memdel((void **)&ctx->bg_jobs);
	ctx->bg_jobs = arr;
	ctx->bg_cnt *= 2;
	return (i);
}

size_t					jc_addtobg(t_ctx *ctx, t_job *j)
{
	size_t				i;
	t_list				*l;

	i = 0;
	while (i < ctx->bg_cnt)
	{
		if (ctx->bg_jobs[i] != NULL && ctx->bg_jobs[i]->pgid == j->pgid)
			return ((size_t)-1);
		i++;
	}
	if ((i = jc_getbgnext(ctx)) == (size_t)-1)
		i = jc_bggrow(ctx);
	if (ctx->fg_job == j)
		ctx->fg_job = NULL;
	ctx->bg_jobs[i] = j;
	j->parent->bg = 1;
	l = list_create(j);
	l->next = ctx->bgs;
	ctx->bgs = l;
	return (i);
}
