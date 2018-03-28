/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 14:35:53 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/28 12:55:20 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void			lrestore(t_ctx *ctx, t_job *j, t_proc *p, t_list **curr)
{
	size_t			i;

	if (j->parent->status & JOB_DON)
		return ;
	i = jc_findid(ctx, j);
	jc_unlistjob(ctx, j, i);
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

static int			lbg_err(t_proc *p)
{
	char			*str;
	t_list			*l;

	ft_asprintf(&str, BU_JOB_ERR, "fg", BU_JOB_NO);
	l = list_create(str);
	ft_assert((void **[]){(void **)&str, (void **)&l}, 2);
	p->data.out = l;
	return (1);
}

int					ft_fg(t_proc *p, t_ctx *ctx, int pipeline)
{
	t_job			*j;

	if (pipeline)
	{
		p->type = BU_STR;
		p->data.str = ft_strdup("221sh: fg: no job control\n");
		return (1);
	}
	p->type = BUILTIN;
	if (p->argv[1] == NULL)
	{
		if (ctx->bgs == NULL)
			return (lbg_err(p));
		j = (t_job *)ctx->bgs->content;
		lrestore(ctx, j, p, &p->data.out);
		return (0);
	}
	lmultiarg(p, ctx);
	return (0);
}
