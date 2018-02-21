/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 16:52:48 by lportay           #+#    #+#             */
/*   Updated: 2018/02/16 11:11:10 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	move_cursor_n_columns(int n)
{
	char *tmp;

	if (!n)
		return ;
	write(STDIN_FILENO, "\E[", 2);
	tmp = ft_itoa(abs(n));
	ft_putstr_fd(tmp, STDIN_FILENO);
	if (n > 0)
		write(STDIN_FILENO, "C", 1);
	else if (n < 0)
		write(STDIN_FILENO, "D", 1);
	free(tmp);
}

void	move_cursor_n_lines(int n)
{
	char *tmp;

	if (!n)
		return ;
	write(STDIN_FILENO, "\E[", 2);
	tmp = ft_itoa(abs(n));
	ft_putstr_fd(tmp, STDIN_FILENO);
	if (n > 0)
		write(STDIN_FILENO, "B", 1);
	else if (n < 0)
		write(STDIN_FILENO, "A", 1);
	free(tmp);
}

void	move_cursor_forward(t_ctx *ctx, t_line *l)
{
	l->cursor_offset++;
	if (!(l->cursor_offset % ctx->ws.ws_col))
		tputs(ctx->tc.dow, 1, &ft_putchar_stdin);
	else
		tputs(ctx->tc.nd, 1, &ft_putchar_stdin);
}

void	move_cursor_backward(t_ctx *ctx, t_line *l)
{
	if (!(l->cursor_offset % ctx->ws.ws_col))
	{
		tputs(ctx->tc.up, 1, &ft_putchar_stdin);
		move_cursor_n_columns(ctx->ws.ws_col);
	}
	else
		tputs(ctx->tc.le, 1, &ft_putchar_stdin);
	l->cursor_offset--;
}

void	move_cursor_end_of_line(t_ctx *ctx, t_line *l)
{
	move_cursor_n_lines(l->num_lines - l->cursor_line);
	tputs(ctx->tc.cr, 1, &ft_putchar_stdin);
	move_cursor_n_columns(l->line_len % ctx->ws.ws_col);
}
