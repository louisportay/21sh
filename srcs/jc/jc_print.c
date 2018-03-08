/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 14:41:53 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/08 15:40:26 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void					jc_notify(t_job *j, int i, int all)
{
	if (j->parent->done == 1)
	{
		if (j->parent->status == 0)
			printf("[%d]%-3c%-24s%s\n", i + 1, ' ', "Done", j->parent->command);
		else
			printf("[%d]%-3c%s %-3d%16c%s\n", i + 1, ' ', "Exit",
					j->parent->status, ' ', j->parent->command);
		get_ctxaddr(NULL)->bg_jobs[i] = NULL;
//		job_safeclear(get_ctxaddr(NULL)->bg_jobs + i);
	}
	else if (all)
		printf("[%d]%-3c%-24s%s\n", i + 1, ' ', "Not done", j->parent->command);
}

void					jc_print(t_ctx *ctx, int all, int verbose)
{
	size_t				i;

	i = 0;
	(void)verbose;
	while (i < ctx->bg_cnt)
	{
		if (ctx->bg_jobs[i] != NULL)
			jc_notify(ctx->bg_jobs[i], (int)i, all);
		i++;
	}
}
