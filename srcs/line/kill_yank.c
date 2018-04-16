/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_yank.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:48:21 by lportay           #+#    #+#             */
/*   Updated: 2018/03/23 14:49:59 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	kill_end(t_ctx *ctx, t_line *l)
{
	if (ctx->yank)
		ft_dlstdel(&ctx->yank, &delvoid);
	ctx->yank = l->line->next;
	l->line->next = NULL;
	ctx->yank->prev = NULL;
	clear_line(ctx, l);
	print_line_attributes(ctx, l, ft_dlstfirst(l->line)->next);
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
	clear_line(ctx, l);
	redraw_line(ctx, l);
	while (l->line != tmp)
		lkey(ctx, l);
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
	clear_line(ctx, l);
	redraw_line(ctx, l);
	while (l->line != tmp)
		lkey(ctx, l);
}

void	kill_next_word(t_ctx *ctx, t_line *l)
{
	t_dlist *tmp;

	if (ctx->yank)
		ft_dlstdel(&ctx->yank, &delvoid);
	ctx->yank = l->line->next;
	ctx->yank->prev = NULL;
	tmp = l->line;
	go_next_word(ctx, l);
	if (l->line->next)
		l->line->next->prev = tmp;
	tmp->next = l->line->next;
	while (ctx->yank != l->line)
		ctx->yank = ctx->yank->next;
	ctx->yank->next = NULL;
	ft_dlsthead(&ctx->yank);
	l->line = tmp;
	clear_line(ctx, l);
	redraw_line(ctx, l);
	while (l->line != tmp)
		lkey(ctx, l);
}

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
