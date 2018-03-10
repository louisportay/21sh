/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 16:52:48 by lportay           #+#    #+#             */
/*   Updated: 2018/03/10 19:56:06 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void handle_move_around_newline(t_ctx *ctx, t_line *l)
{
	t_dlist *tmp;
	int		offset;

	tmp = l->line->prev;
	l->cursor_line--;
	l->cursor_inline--;
	l->offset_inline = 0;
	tputs(ctx->tc.up, 1, &ft_putchar_stdin);

	while (*(char *)tmp->data != '\n')
	{
		l->offset_inline++;
		if (!(l->offset_inline % ctx->ws.ws_col))
			tputs(ctx->tc.cr, 1, &ft_putchar_stdin);
		else
			tputs(ctx->tc.nd, 1, &ft_putchar_stdin);
		tmp = tmp->prev;
		if (!tmp)
		{
	  		offset = (l->cursor_offset - l->offset_inline) % ctx->ws.ws_col;
			while (offset-- != 0)
			{
				tputs(ctx->tc.nd, 1, &ft_putchar_stdin);
				l->offset_inline++;
			}
			break;
		}
	}
	l->inline_len = l->offset_inline;
}

int	move_cursor_backward(t_ctx *ctx, t_line *l)
{
	l->cursor_offset--;
	if (*(char *)l->line->data == '\n')
	{
		handle_move_around_newline(ctx, l);
		return (1);
	}
	else if (!(l->offset_inline % ctx->ws.ws_col))
	{
		tputs(ctx->tc.up, 1, &ft_putchar_stdin);
		l->cursor_line--;
		l->offset_inline--;
		dprintf(ctx->tty, "\E[%dC", ctx->ws.ws_col);
		return (1);
	}
	else
	{
		l->offset_inline--;
		tputs(ctx->tc.le, 1, &ft_putchar_stdin);
		return (0);
	}
}

size_t	get_inline_len(t_dlist *line)
{
	size_t len;

	len = 0;
	while (line->next && *(char *)line->next->data != '\n')
	{
		len++;
		line = line->next;
	}
	return (len);
}



int	move_cursor_forward(t_ctx *ctx, t_line *l)
{
	l->cursor_offset++;
	l->offset_inline++;
	if (*(char *)l->line->next->data == '\n')
	{
		l->cursor_line++;
		l->cursor_inline++;
		l->offset_inline = 0;
		l->inline_len = get_inline_len(l->line->next); //UNDETERMINED
		tputs(ctx->tc.dow, 1, &ft_putchar_stdin);
		return (1);
	}
	else if (!(l->offset_inline % ctx->ws.ws_col))
	{
		tputs(ctx->tc.dow, 1, &ft_putchar_stdin);
		l->cursor_line++;
		return (1);
	}
	else
	{
		tputs(ctx->tc.nd, 1, &ft_putchar_stdin);
		return (0);
	}
}
