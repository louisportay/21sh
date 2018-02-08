/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:10:46 by lportay           #+#    #+#             */
/*   Updated: 2018/02/07 18:36:34 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	go_upper_line(t_ctx *ctx, t_line *l)
{
	int excess_mov;

	tputs(ctx->tc.up, 1, &ft_putchar_stdin);
	l->cursor_offset -= ctx->ws.ws_col;
	excess_mov = move_dlst_head(&l->line, -ctx->ws.ws_col);
	if (excess_mov)
	{
		l->cursor_offset -= excess_mov;
		move_cursor_n_columns(-excess_mov);
	}
}

void	go_lower_line(t_ctx *ctx, t_line *l)
{
	int excess_mov;

	move_cursor_n_lines(1);
	l->cursor_offset += ctx->ws.ws_col;
	excess_mov = move_dlst_head(&l->line, ctx->ws.ws_col);
	if (excess_mov)
	{
		l->cursor_offset = l->line_len;
		move_cursor_n_columns(-excess_mov);
	}
}

void	go_to_line_beginning(t_ctx *ctx, t_line *l)
{
	int excess_mov;

	excess_mov = move_dlst_head(&l->line, -l->cursor_offset);
	while (l->cursor_line--)
		go_upper_line(ctx, l);
	tputs(ctx->tc.cr, 1, &ft_putchar_stdin);
	l->cursor_offset = -excess_mov;
	if (abs(excess_mov))
		move_cursor_n_columns(-excess_mov);
}

void	go_to_line_end(t_ctx *ctx, t_line *l)
{
	move_dlst_head(&l->line, l->line_len - l->cursor_offset);
	move_cursor_n_lines(l->num_lines - l->cursor_line);
	move_cursor_n_columns((l->line_len % ctx->ws.ws_col) -
			l->cursor_offset % ctx->ws.ws_col);
	l->cursor_offset = l->line_len;
}

void	go_to_previous_word(t_ctx *ctx, t_line *l)
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

void	go_to_next_word(t_ctx *ctx, t_line *l)
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
