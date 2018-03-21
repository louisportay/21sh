/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_yank.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:48:21 by lportay           #+#    #+#             */
/*   Updated: 2018/03/21 11:12:03 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	kill_end(t_ctx *ctx, t_line *l)
{
	t_dlist *tmp;

	if (ctx->yank)
		ft_dlstdel(&ctx->yank, &delvoid);
	ctx->yank = l->line->next;
	l->line->next = NULL;
	ctx->yank->prev = NULL;
	tmp = l->line;
	ft_dlsthead(&tmp);
	clear_line(ctx, l);
	print_line_attributes(ctx, l, tmp->next);
}

void	kill_beginning(t_ctx *ctx, t_line *l)
{
	t_dlist		*tmp;

	if (ctx->yank)
		ft_dlstdel(&ctx->yank, &delvoid);
	tmp = l->line->next;
	l->line->next = NULL;
	ft_dlsthead(&l->line);
	ctx->yank = l->line->next;
	ctx->yank->prev = NULL;
	l->line->next = tmp;
	if (tmp)
		tmp->prev = l->line;
	tmp = l->line;
	ft_dlsthead(&tmp);
	clear_line(ctx, l);
	tputs(ctx->tc.sc, 1, &ft_putchar_stdin);
	print_line_attributes(ctx, l, tmp->next);
	tputs(ctx->tc.rc, 1, &ft_putchar_stdin);
}

void	kill_prev_word(t_ctx *ctx, t_line *l)
{
	t_dlist *tmp;

	if (ctx->yank)
		ft_dlstdel(&ctx->yank, &delvoid);
	tmp = l->line->next;
	l->line->next = NULL;
	if (tmp)
		tmp->prev = NULL;
	go_prev_word(ctx, l);
	ctx->yank = l->line->next;
	if (ctx->yank)
		ctx->yank->prev = NULL;
	l->line->next = tmp;
	if (tmp)
		tmp->prev = l->line;
	tmp = l->line;
	ft_dlsthead(&tmp);
	tputs(ctx->tc.sc, 1, &ft_putchar_stdin);
	clear_line(ctx, l);
	print_line_attributes(ctx, l, tmp->next);
	tputs(ctx->tc.rc, 1, &ft_putchar_stdin);
}

void	kill_next_word(t_ctx *ctx, t_line *l)
{
	t_dlist *tmp;

	if (ctx->yank)
		ft_dlstdel(&ctx->yank, &delvoid);
	ctx->yank = l->line->next;
	ctx->yank->prev = NULL;
	tmp = l->line;
	tputs(ctx->tc.sc, 1, &ft_putchar_stdin);
	go_next_word(ctx, l);
	if (l->line->next)
		l->line->next->prev = tmp;
	tmp->next = l->line->next;
	while (ctx->yank != l->line)
		ctx->yank = ctx->yank->next;
	ctx->yank->next = NULL;
	ft_dlsthead(&ctx->yank);
	l->line = tmp;
	ft_dlsthead(&tmp);
	clear_line(ctx, l);
	print_line_attributes(ctx, l, tmp->next);
	tputs(ctx->tc.rc, 1, &ft_putchar_stdin);
}

/*
** Slow but okay
*/

void	yank(t_ctx *ctx, t_line *l)
{
	t_dlist *tmp;

	tmp = l->line->next;
	l->line->next = ft_dlstdup(ctx->yank);
	l->line->next->prev = l->line;
	ft_dlstend(&l->line);
	l->line->next = tmp;
	if (tmp)
		tmp->prev = l->line;
	tmp = l->line;
	clear_line(ctx, l);
	redraw_line(ctx, l);
	while (l->line != tmp)
		lkey(ctx, l);
}
