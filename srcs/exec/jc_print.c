/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:45:08 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/26 20:13:56 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void					jc_print(t_ctx *ctx)
{
	size_t				i;

	printf("# of jobs: %zu\n", ctx->bg_cnt);
	i = 0;
	while (i < ctx->bg_cnt)
	{
		if (ctx->bg_jobs[i] != NULL)
			printf("[%lu]%-4s%-24s%s\n", i + 1, "-", "Stopped", ctx->bg_jobs[i]->command);
		i++;
	}
}
