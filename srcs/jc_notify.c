/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_notify.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:21:35 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/28 15:29:50 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void					jc_notify(t_ctx *ctx)
{
	size_t				i;
	t_job				*j;

	i = 0;
	while (i < ctx->bg_cnt)
	{
		if ((j = ctx->bg_jobs[i]) != NULL && (j->parent->status & JOB_DON))
		{
			if ((j->parent->status & 0xFF) == 0)
			{
				ft_printf("[%d]%-3c%-24s%s\n", i + 1, jc_getstatus(j),
							"Done", j->parent->command);
			}
			else
			{
				ft_printf("[%d]%-3c%s %-19d%s\n", i + 1, jc_getstatus(j),
							"Exit", j->parent->status & 0xFF,
							j->parent->command);
			}
			jc_unlistjob(ctx, j, i);
		}
		i++;
	}
}
