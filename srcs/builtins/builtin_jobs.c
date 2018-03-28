/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 11:59:05 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/28 17:34:52 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void				lprint_pgid(t_ctx *ctx, int flag)
{
	size_t				i;
	t_job				*j;

	i = 0;
	while (i < ctx->bg_cnt)
	{
		if ((j = ctx->bg_jobs[i]) != NULL)
		{
			if ((flag & (BU_J_R | BU_J_S)) == 0
				|| ((flag & BU_J_S) && (j->status & JOB_STP))
				|| ((flag & BU_J_R) && (j->status & JOB_STP) == 0))
				ft_printf("%d\n", j->pgid);
		}
		i++;
	}
}

static void				lprint_all(t_ctx *ctx, int flag)
{
	size_t				i;

	i = 0;
	while (i < ctx->bg_cnt)
	{
		if (ctx->bg_jobs[i] != NULL)
			bu_jobs_print(ctx, i, flag);
		i++;
	}
}

int						ft_jobs(t_proc *p, t_ctx *ctx)
{
	int					flag;

	p->type = BU_STR;
	if ((flag = bu_jobs_args(p)) == -1)
		return (1);
	if (flag & BU_J_P)
		lprint_pgid(ctx, flag);
	else if (flag & BU_J_L)
		bu_jobs_long(ctx, flag);
	else
		lprint_all(ctx, flag);
	jc_notify(ctx);
	return (0);
}
