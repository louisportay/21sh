/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 16:52:48 by lportay           #+#    #+#             */
/*   Updated: 2018/03/25 20:42:02 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	munch_prompt_len(t_ctx *ctx, t_line *l, int offset)
{
	while (offset-- > 0)
	{
		tputs(ctx->tc.nd, 1, &ft_putchar_stdin);
		l->offset_inline++;
		if (!(l->offset_inline % ctx->ws.ws_col))
			tputs(ctx->tc.cr, 1, &ft_putchar_stdin);
	}
}

static void	handle_move_around_newline(t_ctx *ctx, t_line *l)
{
	t_dlist *tmp;

	tmp = l->line->prev;
	l->cursor_line--;
	l->offset_inline = 0;
	tputs(ctx->tc.up, 1, &ft_putchar_stdin);
	while (*(char *)tmp->data != '\n')
	{
		if (!tmp->prev)
		{
			munch_prompt_len(ctx, l, l->prompt_len);
			break ;
		}
		l->offset_inline++;
		if (!(l->offset_inline % ctx->ws.ws_col))
			tputs(ctx->tc.cr, 1, &ft_putchar_stdin);
		else
			tputs(ctx->tc.nd, 1, &ft_putchar_stdin);
		tmp = tmp->prev;
	}
}

int			move_cursor_backward(t_ctx *ctx, t_line *l)
{
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
		ft_dprintf(ctx->tty, "\E[%dC", ctx->ws.ws_col);
		return (1);
	}
	else
	{
		l->offset_inline--;
		tputs(ctx->tc.le, 1, &ft_putchar_stdin);
		return (0);
	}
}

int			move_cursor_forward(t_ctx *ctx, t_line *l)
{
	l->offset_inline++;
	if (*(char *)l->line->next->data == '\n')
	{
		l->cursor_line++;
		l->offset_inline = 0;
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
