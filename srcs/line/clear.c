/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:52:05 by lportay           #+#    #+#             */
/*   Updated: 2018/04/06 20:54:29 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
** Redraw the whole line and get whole attributes values
*/

void	redraw_line(t_ctx *ctx, t_line *l)
{
	ft_dlsthead(&l->line);
	print_line_attributes(ctx, l, l->line->next);
	ft_dlstend(&l->line);
}

/*
** Window size change
*/

void	clear_line(t_ctx *ctx, t_line *l)
{
	if (l->cursor_line)
		ft_dprintf(STDIN_FILENO, "\033[%dA", l->cursor_line);
	tputs(ctx->tc.cr, 1, &ft_putchar_stdin);
	tputs(ctx->tc.cd, 1, &ft_putchar_stdin);
	reset_attributes(l);
}

/*
** Ctrl-L
*/

void	clear_screen_(t_ctx *ctx, t_line *l)
{
	tputs(ctx->tc.cl, 1, &ft_putchar_stdin);
	reset_attributes(l);
	redraw_line(ctx, l);
}
