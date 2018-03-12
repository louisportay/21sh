/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:10:46 by lportay           #+#    #+#             */
/*   Updated: 2018/03/12 13:25:08 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	go_upper_line(t_ctx *ctx, t_line *l)
{
	int mov;

	mov = ctx->ws.ws_col;
	while (mov-- && l->line->prev)
		lkey(ctx, l);
}

void	go_lower_line(t_ctx *ctx, t_line *l)
{
	int mov;

	mov = ctx->ws.ws_col;
	while (mov-- && l->line->next)
		rkey(ctx, l);

}

//void	go_upper_line(t_ctx *ctx, t_line *l)
//{
//	int		mov;
//	bool	nl;
//	unsigned	off;
//  
//	mov = ctx->ws.ws_col;
//	nl = true;
//	off = l->offset_inline;
//	while (mov && l->line->prev)
//	{
//		if (move_cursor_backward(ctx, l) && *(char *)l->line->prev->data == '\n')
//			nl = false;
//		l->line = l->line->prev;
//
//		if (*(char *)l->line->data == '\n')
//		{
//			if (nl == true)
//			{
//				if (off > (l->offset_inline % ctx->ws.ws_col))
//					break;
//				mov = (l->offset_inline % ctx->ws.ws_col) - off;
//				nl = false;
//			}
//			else
//				break ;
//		}
//		else
//			mov--;
//	}
//}

//void	go_lower_line(t_ctx *ctx, t_line *l)
//{
//	int		mov;
//	bool	nl;
//  
//	mov = ctx->ws.ws_col;
//	nl = true;
//	while (mov && l->line->next)
//	{
//		if (*(char *)l->line->next->data == '\n')
//		{
//			if (nl == true)
//			{
//				mov = (mov - (ctx->ws.ws_col - l->offset_inline)) % ctx->ws.ws_col;
//				nl = false;
//			}
//			else
//				break ;
//		}
//		else
//			mov--;
//	if (move_cursor_forward(ctx, l))
//		nl = false;
//	l->line = l->line->next;
//	}
//}

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
