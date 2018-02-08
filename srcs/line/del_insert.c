/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:44:52 by lportay           #+#    #+#             */
/*   Updated: 2018/02/07 18:37:20 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void del_char(t_ctx *ctx, t_line *l)
{
	l->line_len--;
	ft_dlstremove(&l->line, &ft_memdel);
	if (l->multiline)
	{
		tputs(ctx->tc.cd, 1, &ft_putchar_stdin);
		tputs(ctx->tc.sc, 1, &ft_putchar_stdin);
		print_line(l->line->next);
		tputs(ctx->tc.rc, 1, &ft_putchar_stdin);
	}
	else
		tputs(ctx->tc.dc, 1, &ft_putchar_stdin);
}
void	del_current_char(t_ctx *ctx, t_line *l)
{
	l->line = l->line->next;
	del_char(ctx, l);
}

void	del_previous_char(t_ctx *ctx, t_line *l)
{
	move_cursor_backward(ctx, l);
	l->cursor_line = l->cursor_offset / ctx->ws.ws_col;
	if (!l->multiline && l->cursor_line < l->num_lines)
		l->multiline = true;
	del_char(ctx, l);
}

void	insert_char(char *buf, t_ctx *ctx, t_line *l)
{
	l->line_len++;
	l->num_lines = l->line_len / ctx->ws.ws_col;
	ft_dlstinsert(l->line, ft_dlstnew(ft_strdup(buf)));
	l->line = l->line->next;
	if (l->multiline)
	{
		tputs(ctx->tc.cd, 1, &ft_putchar_stdin);
		print_line(l->line);
		if (!(l->line_len % ctx->ws.ws_col))
			tputs(ctx->tc.dow, 1, &ft_putchar_stdin);
		move_cursor_n_lines(-(l->num_lines - l->cursor_line));
		move_cursor_n_columns(l->cursor_offset % ctx->ws.ws_col - l->line_len % ctx->ws.ws_col);
	}
	else if (!l->multiline)
	{
		write(STDOUT_FILENO, buf, 1);
		tputs(ctx->tc.le, 1, &ft_putchar_stdin);
	}
	move_cursor_forward(ctx, l);
}
