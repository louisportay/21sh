/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:52:05 by lportay           #+#    #+#             */
/*   Updated: 2018/03/06 20:19:43 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Called when the window size changes and for CTRL-L trigger
** Redraw the whole line with the prompt
*/

void	redraw_line(t_ctx *ctx, t_line *l)
{
	if (l->line)
	{
		ft_dlsthead(&l->line);
		print_line_cursor(l, l->line->next);
		ft_dlstend(&l->line);
	}
	else
		print_line_cursor(l, T_HISTENTRY(ctx->hist.list->data)->line->next);
	if (!(l->cursor_offset % ctx->ws.ws_col))
		tputs(ctx->tc.dow, 1, &ft_putchar_stdin);
}

void clear_line(t_ctx *ctx, t_line *l)
{
//	tputs(ctx->tc.cr, 1, &ft_putchar_stdin);
//	move_cursor_n_lines(-l->cursor_line);
	go_beginning(ctx, l);
	tputs(ctx->tc.cd, 1, &ft_putchar_stdin);
}

void	clear_screen_(t_ctx *ctx, t_line *l)
{
	tputs(ctx->tc.cl, 1, &ft_putchar_stdin);
	l->cursor_offset = 0;
	print_prompt(ctx);
	redraw_line(ctx, l);
}
