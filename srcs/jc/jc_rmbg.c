/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_rmbg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 10:48:20 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/11 11:33:43 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void					jc_rmbg(t_ctx *ctx, t_job *j)
{
	size_t				i;
	t_list				*l;
	t_list				*p;

	if ((i = jc_ctxfind(ctx, j->pgid)) == (size_t)-1)
		return ;
	ctx->bg_jobs[i] = NULL;
	l = ctx->bgs;
	p = NULL;
	while (l != NULL)
	{
		if ((t_job *)l->content == j)
		{
			if (p == NULL)
				ctx->bgs = l->next;
			else
				p->next = l->next;
			break ;
		}
		p = l;
		l = l->next;
	}
}
