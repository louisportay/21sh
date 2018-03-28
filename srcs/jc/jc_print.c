/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 13:10:43 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/28 14:40:39 by vbastion         ###   ########.fr       */
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
				|| ((flag & BU_J_R) && (j->status & (JOB_STP | JOB_CMP)) == 0))
				ft_printf("%d\n", j->pgid);
		}
		i++;
	}
}

static void				lprint_job(t_ctx *ctx, size_t i, int flag)
{
	t_job				*j;

	j = ctx->bg_jobs[i];
	if (j->parent->status & JOB_DON)
	{
		if (flag & (BU_J_S | BU_J_A))
			return ;
		if ((j->parent->status & 0xFF) == 0)
			ft_printf("[%d]%-3c%-24s%s\n", i + 1, jc_getstatus(j), "Done",
						j->parent->command);
		else
			ft_printf("[%d]%-3c%s %-19d%s\n", i + 1, jc_getstatus(j), "Exit",
						j->parent->status & 0xFF, j->parent->command);
		jc_unlistjob(ctx, j, (size_t)-1);
		job_safeclear(&j->parent);
	}
	else if ((flag & BU_J_A) && j->status & JOB_SIG)
	{
		if (flag & BU_J_S)
			return ;
		ft_printf("[%d]%c  %-12s%-12d%s\n", i + 1, jc_getstatus(j),
					"Terminated: ", j->status & 0xFF, j->parent->command);
		jc_unlistjob(ctx, j, (size_t)-1);
		job_safeclear(&j->parent);
	}
	else if ((flag & BU_J_A) && j->status & JOB_STP)
	{
		if (flag & BU_J_R)
			return ;
		ft_printf("[%d]%-3c%-24s%s\n", i + 1, jc_getstatus(j), "Stopped",
					j->parent->command);
	}
	else if ((flag & BU_J_A))
	{
		if (flag & BU_J_S)
			return ;
		ft_printf("[%d]%-3c%-24s%s &\n", i + 1, jc_getstatus(j), "Running",
					j->parent->command);
	}
}

static void				lprint_all(t_ctx *ctx, int flag)
{
	size_t				i;

	i = 0;
	while (i < ctx->bg_cnt)
	{
		if (ctx->bg_jobs[i] != NULL)
			lprint_job(ctx, i, flag);
		i++;
	}
}

void					jc_print(t_ctx *ctx, int all, int flag)
{
	size_t				i;

	i = 0;
	if (all)
	{
		if (flag & BU_J_P)
			lprint_pgid(ctx, flag | BU_J_A);
		else
			lprint_all(ctx, flag | BU_J_A);
	}
	lprint_all(ctx, 0);
}
