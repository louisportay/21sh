/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_yank.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:48:21 by lportay           #+#    #+#             */
/*   Updated: 2018/03/12 17:40:43 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	kill_end(t_ctx *ctx, t_line *l)
{
	t_dlist *tmp;
	
	if (l->yank)
		ft_dlstdel(&l->yank, &delvoid);
	l->yank = l->line->next;
	l->line->next = NULL;
	l->yank->prev = NULL;	
	tmp = l->line;
	ft_dlsthead(&tmp);
	clear_line(ctx, l);
	print_line_attributes(ctx, l, tmp->next);
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

	if (l->yank)
		ft_dlstdel(&l->yank, &delvoid);
	l->yank = l->line->next;
	l->yank->prev = NULL;
	tmp = l->line;
	tputs(ctx->tc.sc, 1, &ft_putchar_stdin);
	go_next_word(ctx, l);
	if (l->line->next)
		l->line->next->prev = tmp;
	tmp->next = l->line->next;
	while (l->yank != l->line)
		l->yank = l->yank->next;
	l->yank->next = NULL;
	ft_dlsthead(&l->yank);
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
	l->line->next = ft_dlstdup(l->yank);
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
