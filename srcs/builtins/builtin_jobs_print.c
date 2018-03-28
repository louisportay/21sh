/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:56:18 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/28 16:03:31 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char					jc_getstatus(t_job *j)
{
	t_ctx				*ctx;

	ctx = get_ctxaddr();
	if (ctx->bgs != NULL && (t_job *)ctx->bgs->content == j)
		return ('+');
	else if (ctx->bgs->next != NULL
				&& (t_job *)ctx->bgs->next->content == j)
		return ('-');
	else
		return (' ');
}

static void				ljob_don(t_job *j, size_t i, int flag, t_ctx *ctx)
{
	if (flag & BU_J_S)
		return ;
	if ((j->parent->status & 0xFF) == 0)
		ft_printf("[%d]%-3c%-24s%s\n", i + 1, jc_getstatus(j), "Done",
					j->parent->command);
	else
		ft_printf("[%d]%-3c%s %-19d%s\n", i + 1, jc_getstatus(j), "Exit",
					j->parent->status & 0xFF, j->parent->command);
	jc_unlistjob(ctx, j, i);
	job_safeclear(&j->parent);
}

static void				ljob_sig(t_job *j, size_t i, int flag, t_ctx *ctx)
{
	if (flag & BU_J_S)
		return ;
	ft_printf("[%d]%c  %-12s%-12d%s\n", i + 1, jc_getstatus(j),
				"Terminated: ", j->status & 0xFF, j->parent->command);
	jc_unlistjob(ctx, j, i);
	job_safeclear(&j->parent);
}


void					bu_jobs_print(t_ctx *ctx, size_t i, int flag)
{
	t_job				*j;

	j = ctx->bg_jobs[i];
	if (j->parent->status & JOB_DON)
		ljob_don(j, i, flag, ctx);
	else if (j->status & JOB_SIG)
		ljob_sig(j, i, flag, ctx);
	else if (j->status & JOB_STP)
	{
		if (flag & BU_J_R)
			return ;
		ft_printf("[%d]%-3c%-24s%s\n", i + 1, jc_getstatus(j), "Stopped",
					j->parent->command);
	}
	else
	{
		if (flag & BU_J_S)
			return ;
		ft_printf("[%d]%-3c%-24s%s &\n", i + 1, jc_getstatus(j), "Running",
					j->parent->command);
	}
}
