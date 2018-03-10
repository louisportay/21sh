/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:44:52 by lportay           #+#    #+#             */
/*   Updated: 2018/03/10 20:52:57 by lportay          ###   ########.fr       */
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

	if (*(char *)l->line->data == '\n')
	{
		l->inlines--;
		l->num_lines--;
		l->inline_len += get_inline_len(l->line);
	}
	else
		l->inline_len--;
	del_char(ctx, l);
}

void	del_prev_char(t_ctx *ctx, t_line *l)
{
	if (*(char *)l->line->data == '\n')
		l->inlines--;
	else
		l->inline_len--;
	if (move_cursor_backward(ctx, l) == 1)
		l->num_lines--;
	del_char(ctx, l);
}

void	insert_char(char *buf, t_ctx *ctx, t_line *l)
{
	l->line_len++;
	l->inline_len++;
	ft_dlstinsert(l->line, ft_dlstnew(buf, 1));

	tputs(ctx->tc.cd, 1, &ft_putchar_stdin);
	tputs(ctx->tc.sc, 1, &ft_putchar_stdin);
	print_line_nl(ctx, l, l->line->next);
	tputs(ctx->tc.rc, 1, &ft_putchar_stdin);

	l->num_lines += move_cursor_forward(ctx, l);
	l->line = l->line->next;
}
