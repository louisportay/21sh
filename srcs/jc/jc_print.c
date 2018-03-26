/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 13:10:43 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/25 20:41:42 by vbastion         ###   ########.fr       */
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

void					jc_notify(t_job *j, t_ctx *ctx, int i, int all)
{
	if (j->parent->status & JOB_DON)
	{
		if ((j->parent->status & 0xFF) == 0)
			ft_printf("[%d]%-3c%-24s%s\n", i + 1, jc_getstatus(j), "Done",
						j->parent->command);
		else
			ft_printf("[%d]%-3c%s %-19d%s\n", i + 1, jc_getstatus(j), "Exit",
						j->parent->status & 0xFF, j->parent->command);
		jc_rmbg(ctx, j);
		job_safeclear(&j->parent);
	}
	else if (all && j->status & JOB_SIG)
	{
		ft_printf("[%d]%c  %-12s%-12d%s\n", i + 1, jc_getstatus(j),
					"Terminated: ", j->status & 0xFF, j->parent->command);
		jc_rmbg(ctx, j);
		job_safeclear(&j->parent);
	}
	else if (all && j->status & JOB_STP)
		ft_printf("[%d]%-3c%-24s%s\n", i + 1, jc_getstatus(j), "Stopped",
					j->parent->command);
	else if (all)
		ft_printf("[%d]%-3c%-24s%s &\n", i + 1, jc_getstatus(j), "Running",
					j->parent->command);
}

void					jc_print(t_ctx *ctx, int all, int verbose)
{
	size_t				i;

	i = 0;
	while (i < ctx->bg_cnt)
	{
		if (ctx->bg_jobs[i] != NULL)
			jc_notify(ctx->bg_jobs[i], ctx, (int)i, all);
		i++;
	}
	(void)verbose;
}
