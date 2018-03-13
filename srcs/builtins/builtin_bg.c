/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 14:35:55 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/13 13:58:36 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void			ldobg(t_job *j, t_proc *bu, t_list **curr, t_ctx *ctx)
{
	size_t			i;
	char			*str;
	t_list			*l;

	if (j == NULL)
		return ;
	i = jc_findid(ctx, j);
	if (i == (size_t)-1)
		asprintf(&str, BU_JOB_ERR, "bg", BU_JOB_NO);
	else if (j->stopped == 0)
		asprintf(&str, "221sh: bg: job %zu already in background\n", i + 1);
	else
	{
		asprintf(&str, "1[%zu]%-2c%s &\n", i + 1, jc_getstatus(j),
					j->parent->command);
	}
	l = list_create(str);
	if (curr != NULL)
		ft_list_insert(&bu->data.out, curr, l);
	else
		bu->data.out = l;
	if (i != (size_t)-1)
		jc_restore(j);
}

static void			lmultiarg(t_proc *p, t_ctx *ctx)
{
	t_job			*j;
	size_t			k;
	char			*str;
	t_list			*curr;
	t_list			*l;

	curr = NULL;
	k = 1;
	while (p->argv[k] != NULL)
	{
		if ((j = jc_jobspec(p->argv[k], ctx)) != NULL)
			ldobg(j, p, &curr, ctx);
		else
		{
			asprintf(&str, BU_JOB_ERR, "bg", BU_JOB_NO);
			l = list_create(str);
			ft_list_insert(&p->data.out, &curr, l);
		}
		k++;
	}
}

int					ft_bg(t_proc *p, t_ctx *ctx)
{
	t_job			*j;
	char			*str;

	j = NULL;
	p->type = BUILTIN;
	if (p->argv[1] == NULL)
	{
		if (ctx->bgs == NULL)
		{
			asprintf(&str, BU_JOB_ERR, "bg", BU_JOB_NO);
			p->data.out = list_create(str);
		}
		else
			ldobg((t_job *)ctx->bgs->content, p, NULL, ctx);
	}
	else
		lmultiarg(p, ctx);
	return (0);
}
