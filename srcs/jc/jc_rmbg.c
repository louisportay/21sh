/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_rmbg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 10:48:20 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/28 14:10:48 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void					jc_unlistjob(t_ctx *ctx, t_job *j, size_t i)
{
	t_list				*prev;
	t_list				*curr;

	if (i == (size_t)-1)
	{
		if ((i = jc_ctxfind(ctx, j->pgid)) == (size_t)-1)
			return ;
	}
	ctx->bg_jobs[i] = NULL;
	prev = NULL;
	curr = ctx->bgs;
	while (curr != NULL)
	{
		if ((t_job *)curr->content == j)
		{
			if (prev == NULL)
				ctx->bgs = curr->next;
			else
				prev->next = curr->next;
			ft_memdel((void **)&curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}
