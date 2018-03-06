/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:44:52 by lportay           #+#    #+#             */
/*   Updated: 2018/03/06 20:30:14 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void del_char(t_ctx *ctx, t_line *l)
{
	l->line_len--;
	ft_dlstremove(&l->line, &delvoid);
	tputs(ctx->tc.cd, 1, &ft_putchar_stdin);
	tputs(ctx->tc.sc, 1, &ft_putchar_stdin);
	print_line(l->line->next);
	tputs(ctx->tc.rc, 1, &ft_putchar_stdin);
}

void	del_curr_char(t_ctx *ctx, t_line *l)
{
	l->line = l->line->next;
	del_char(ctx, l);
}

void	del_prev_char(t_ctx *ctx, t_line *l)
{
	move_cursor_backward(ctx, l);
	l->cursor_line = l->cursor_offset / ctx->ws.ws_col;
	del_char(ctx, l);
}

void	insert_char(char *buf, t_ctx *ctx, t_line *l)
{
	l->line_len++;
	l->num_lines = l->line_len / ctx->ws.ws_col;
	ft_dlstinsert(l->line, ft_dlstnew(buf, 1));
	l->line = l->line->next;
	tputs(ctx->tc.cd, 1, &ft_putchar_stdin);
	tputs(ctx->tc.sc, 1, &ft_putchar_stdin);
	print_line(l->line);
	tputs(ctx->tc.rc, 1, &ft_putchar_stdin);
	move_cursor_forward(ctx, l);
}
