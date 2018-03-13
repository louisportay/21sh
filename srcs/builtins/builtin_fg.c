/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 14:35:53 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/13 13:58:47 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void			jc_remove(t_ctx *ctx, t_job *job, size_t i)
{
	t_list			*prev;
	t_list			*curr;

	prev = NULL;
	curr = ctx->bgs;
	ctx->bg_jobs[i] = NULL;
	while (curr != NULL)
	{
		if ((t_job *)curr->content == job)
		{
			if (prev == NULL)
				ctx->bgs = curr->next;
			else
				prev->next = curr->next;
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

static void			lmultiarg(t_proc *p, t_ctx *ctx)
{
	size_t			i;
	size_t			k;
	t_job			*j;
	char			*str;
	t_list			*lsts[2];

	k = 1;
	lsts[0] = NULL;
	while (p->argv[k] != NULL)
	{
		if ((j = jc_jobspec(p->argv[k], ctx)) != NULL)
		{
			i = jc_findid(ctx, j);
			jc_remove(ctx, j, i);
			jc_restore(j);
			job_putfg(j, ctx);
		}
		else
		{
			asprintf(&str, BU_JOB_ERR, "fg", BU_JOB_NO);
			lsts[1] = list_create(str);
			ft_list_insert(&p->data.out, &lsts[0], lsts[1]);
		}
		k++;
	}
}

int					ft_fg(t_proc *p, t_ctx *ctx)
{
	size_t			i;
	t_job			*j;
	char			*str;

	p->type = BUILTIN;
	if (p->argv[1] == NULL)
	{
		if (ctx->bgs == NULL)
		{
			asprintf(&str, BU_JOB_ERR, "fg", BU_JOB_NO);
			p->data.out = list_create(str);
		}
		else
		{
			j = (t_job *)ctx->bgs->content;
			i = jc_findid(ctx, j);
			jc_remove(ctx, j, i);
			jc_restore(j);
			job_putfg(j, ctx);
		}
	}
	else
		lmultiarg(p, ctx);
	return (0);
}
