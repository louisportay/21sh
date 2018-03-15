/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 14:35:53 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/15 16:37:53 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				jc_remove(t_ctx *ctx, t_job *job, size_t i)
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

static void 		lrestore(t_ctx *ctx, t_job *j, t_proc *p, t_list **curr)
{
	size_t			i;

	if (j->parent->status & JOB_DON)
		return ;
	i = jc_findid(ctx, j);
	jc_remove(ctx, j, i);
	signal(SIGCHLD, SIG_IGN);
	jc_restore(j, p, curr);
	j->bg = 0;
	j->parent->bg = 0;
	job_next(j, ctx);
	signal(SIGCHLD, &jc_signal);
}

static void			lmultiarg(t_proc *p, t_ctx *ctx)
{
	size_t			k;
	t_job			*j;
	t_list			*curr;

	k = 1;
	curr = NULL;
	while (p->argv[k] != NULL)
	{
		if ((j = jc_jobspec(p, "fg", p->argv[k], ctx)) != NULL)
			lrestore(ctx, j, p, &curr);
		k++;
	}
}

int					ft_fg(t_proc *p, t_ctx *ctx)
{
	t_job			*j;
	char			*str;
	t_list			*l;

	p->type = BUILTIN;
	if (p->argv[1] == NULL)
	{
		if (ctx->bgs == NULL)
		{
			asprintf(&str, BU_JOB_ERR, "fg", BU_JOB_NO);
			l = list_create(str);
			ft_assert((void **[]){(void **)&str, (void **)&l}, 2);
			p->data.out = l;
		}
		else
		{
			j = (t_job *)ctx->bgs->content;
			lrestore(ctx, j, p, &p->data.out);
		}
	}
	else
		lmultiarg(p, ctx);
	return (0);
}
