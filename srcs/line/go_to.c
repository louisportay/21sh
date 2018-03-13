/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:10:46 by lportay           #+#    #+#             */
/*   Updated: 2018/03/13 19:34:17 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	go_upper_line(t_ctx *ctx, t_line *l)
{
	int mov;
	bool nl;

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
	int mov;
	bool nl;

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

void	go_beginning(t_ctx *ctx, t_line *l)
{
	while (l->line->prev)
		lkey(ctx, l);
}

void	go_end(t_ctx *ctx, t_line *l)
{
	while (l->line->next)
		rkey(ctx, l);
}

void	go_prev_word(t_ctx *ctx, t_line *l)
{
	bool inword;

	inword = (ft_isalnum(*(char *)l->line->data) == true) ? true : false;
	while (!inword && l->line->prev)
	{
		if (ft_isalnum(*(char *)l->line->data) == true)
			inword = true;
		lkey(ctx, l);
	}
	while (inword == true && l->line->prev)
	{
		if (!(ft_isalnum(*(char *)l->line->data)))
			break;
		lkey(ctx, l);
	}
}

void	go_next_word(t_ctx *ctx, t_line *l)
{
	bool inword;

	inword = (ft_isalnum(*(char *)l->line->next->data) == true) ? true : false;
	while (!inword && l->line->next)
	{
		if (ft_isalnum(*(char *)l->line->next->data) == true)
		{
			inword = true;
			break;
		}
		rkey(ctx, l);
	}
	while (inword == true && l->line->next)
	{
		if (!(ft_isalnum(*(char *)l->line->next->data)))
			break;
		rkey(ctx, l);
	}
}
