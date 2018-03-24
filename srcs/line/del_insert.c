/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:44:52 by lportay           #+#    #+#             */
/*   Updated: 2018/03/23 15:58:19 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	del_char(t_ctx *ctx, t_line *l)
{
	ft_dlstremove(&l->line, &delvoid);
	tputs(ctx->tc.cd, 1, &ft_putchar_stdin);
	tputs(ctx->tc.sc, 1, &ft_putchar_stdin);
	print_line(l->line->next);
	tputs(ctx->tc.rc, 1, &ft_putchar_stdin);
}

void		del_curr_char(t_ctx *ctx, t_line *l)
{
	l->line = l->line->next;
	if (*(char *)l->line->data == '\n')
		l->num_lines--;
	del_char(ctx, l);
}

void		del_prev_char(t_ctx *ctx, t_line *l)
{
	if (move_cursor_backward(ctx, l) == 1)
		l->num_lines--;
	del_char(ctx, l);
}

void		insert_char(char *buf, t_ctx *ctx, t_line *l)
{
	t_dlist *tmp;

	ft_dlstinsert(l->line, ft_dlstnew(buf, 1));
	tmp = l->line->next;
	clear_line(ctx, l);
	redraw_line(ctx, l);
	while (l->line != tmp)
		lkey(ctx, l);
}
