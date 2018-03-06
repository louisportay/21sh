/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_yank.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:48:21 by lportay           #+#    #+#             */
/*   Updated: 2018/03/06 19:55:01 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Used to kill a region
*/

static void	print_rest_of_line(t_ctx *ctx, t_line *l)
{
	unsigned tmp;

	tmp = l->cursor_offset;
	tputs(ctx->tc.sc, 1, &ft_putchar_stdin);
	print_line_cursor(l, l->line->next);
	tputs(ctx->tc.rc, 1, &ft_putchar_stdin);
	l->line_len = l->cursor_offset;
	l->cursor_offset = tmp;
	if (!(l->cursor_offset % ctx->ws.ws_col))
		tputs(ctx->tc.dow, 1, &ft_putchar_stdin);
}

void	kill_end(t_ctx *ctx, t_line *l)
{
	if (l->yank)
		ft_dlstdel(&l->yank, &delvoid);
	l->yank = l->line->next;
	l->line->next = NULL;
	l->yank->prev = NULL;
	l->line_len = l->cursor_offset;
	tputs(ctx->tc.cd, 1, &ft_putchar_stdin);
}

void	kill_beginning(t_ctx *ctx, t_line *l)
{
	t_dlist		*tmp;

	if (l->yank)
		ft_dlstdel(&l->yank, &delvoid);
	tmp = l->line->next;
	l->line->next = NULL;
	ft_dlsthead(&l->line);
	l->yank = l->line->next;
	l->yank->prev = NULL;
	l->line->next = tmp;
	if (tmp)
		tmp->prev = l->line;
	clear_line(ctx, l);
//	l->cursor_offset = 0;
//	print_prompt(ctx);
	print_rest_of_line(ctx, l);
}

void	kill_prev_word(t_ctx *ctx, t_line *l)
{
	t_dlist *tmp;

	if (l->yank)
		ft_dlstdel(&l->yank, &delvoid);
	tmp = l->line->next;
	l->line->next = NULL;
	if (tmp)
		tmp->prev = NULL;
	go_prev_word(ctx, l);
	l->yank = l->line->next;
	if (l->yank)
		l->yank->prev = NULL;
	l->line->next = tmp;
	if (tmp)
		tmp->prev = l->line;
	tputs(ctx->tc.cd, 1, &ft_putchar_stdin);
	print_rest_of_line(ctx, l);
}

void	kill_next_word(t_ctx *ctx, t_line *l)
{
	t_dlist *tmp;
	int		offset;

	if (l->yank)
		ft_dlstdel(&l->yank, &delvoid);
	l->yank = l->line->next;
	l->yank->prev = NULL;
	offset = l->cursor_offset;
	tmp = l->line;

	tputs(ctx->tc.sc, 1, &ft_putchar_stdin);
	go_next_word(ctx, l);
	tputs(ctx->tc.rc, 1, &ft_putchar_stdin);
	l->cursor_offset = offset;
	tmp->next = l->line->next;
	l->line->next = NULL;
	l->line = tmp;
	tputs(ctx->tc.cd, 1, &ft_putchar_stdin);
	print_rest_of_line(ctx, l);	
}

void	yank(t_ctx *ctx, t_line *l)
{
	t_dlist *tmp;

	tmp = l->line->next;
	l->line->next = ft_dlstdup(l->yank);
	l->line->next->prev = l->line;
	tputs(ctx->tc.cd, 1, &ft_putchar_stdin);
	print_line_cursor_len(l, l->line->next);
	ft_dlstend(&l->line);
	l->line->next = tmp;
	if (tmp)
		tmp->prev = l->line;
	tputs(ctx->tc.sc, 1, &ft_putchar_stdin);
	print_line(l->line->next);
	tputs(ctx->tc.rc, 1, &ft_putchar_stdin);
	if (!(l->cursor_offset % ctx->ws.ws_col))
		tputs(ctx->tc.dow, 1, &ft_putchar_stdin);
}
