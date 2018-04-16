/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_line.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:55:35 by lportay           #+#    #+#             */
/*   Updated: 2018/03/14 13:55:37 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	go_upper_line(t_ctx *ctx, t_line *l)
{
	int		mov;
	bool	nl;

	mov = ctx->ws.ws_col;
	nl = false;
	while (mov > 0 && l->line->prev)
	{
		lkey(ctx, l);
		if (*(char *)l->line->next->data == '\n')
		{
			if (nl == false)
			{
				mov -= (ctx->ws.ws_col - (l->offset_inline % ctx->ws.ws_col));
				nl = true;
			}
			else
				break ;
		}
		else
			mov--;
	}
}

void	go_lower_line(t_ctx *ctx, t_line *l)
{
	int		mov;
	bool	nl;

	mov = ctx->ws.ws_col;
	nl = false;
	while (mov > 0 && l->line->next)
	{
		if (*(char *)l->line->next->data == '\n')
		{
			if (nl == false)
			{
				mov -= (ctx->ws.ws_col - (l->offset_inline % ctx->ws.ws_col));
				nl = true;
			}
			else
				break ;
		}
		else
			mov--;
		if (move_cursor_forward(ctx, l) && nl == false)
			nl = true;
		l->line = l->line->next;
	}
}
