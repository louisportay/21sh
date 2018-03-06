/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 17:42:27 by lportay           #+#    #+#             */
/*   Updated: 2018/03/06 19:55:09 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Will eventually update the history entry, if it is modified
*/

static void	load_histentry(t_ctx *ctx, t_line *l)
{
	if (l->line)
		ft_dlsthead(&l->line);
	if (ctx->hist.list->prev && l->line && l->line != l->lastline)
	{
		ft_dlstdel(&T_HISTENTRY(ctx->hist.list->data)->line, &delvoid);
		T_HISTENTRY(ctx->hist.list->data)->line = l->line;
	}
}

/*
** These 2 functions will print the histentry before loading them to be changed.
** They're changed when the user do something else than scrolling with UP and
** and DOWN KEYS. (See `user_input' first condition which call `load_line')
*/

void	up_key(t_ctx *ctx, t_line *l)
{
	clear_line(ctx, l);
//	l->cursor_offset = 0;
//	print_prompt(ctx);
	l->line_len = l->cursor_offset;
	load_histentry(ctx, l);
	ctx->hist.list = ctx->hist.list->next;
	print_line_cursor_len(l, T_HISTENTRY(ctx->hist.list->data)->line->next);
	l->line = NULL;
	if (!(ctx->line.cursor_offset % ctx->ws.ws_col))
		tputs(ctx->tc.dow, 1, &ft_putchar_stdin);
}

void	down_key(t_ctx *ctx, t_line *l)
{
	clear_line(ctx, l);
//	l->cursor_offset = 0;
//	print_prompt(ctx);
	l->line_len = l->cursor_offset;
	load_histentry(ctx, l);
	ctx->hist.list = ctx->hist.list->prev;
	if (!ctx->hist.list->prev)
	{
		l->line = l->lastline;
		print_line_cursor_len(l, l->line->next);
		ft_dlstend(&l->line);
	}
	else
	{
		print_line_cursor_len(l, T_HISTENTRY(ctx->hist.list->data)->line->next);
		l->line = NULL;
	}
	if (!(l->cursor_offset % ctx->ws.ws_col))
		tputs(ctx->tc.dow, 1, &ft_putchar_stdin);
}
