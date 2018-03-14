/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 17:42:27 by lportay           #+#    #+#             */
/*   Updated: 2018/03/13 18:55:33 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	update_histentry(t_ctx *ctx, t_line *l)
{
	ft_dlsthead(&l->line);
	if (ctx->hist.list->prev && l->line && l->line != l->lastline)
	{
		ft_dlstdel(&T_HISTENTRY(ctx->hist.list->data)->line, &delvoid);
		T_HISTENTRY(ctx->hist.list->data)->line = l->line;
	}
}

void		up_key(t_ctx *ctx, t_line *l)
{
	update_histentry(ctx, l);
	ctx->hist.list = ctx->hist.list->next;
	l->line = ft_dlstdup(T_HISTENTRY(ctx->hist.list->data)->line);
	clear_line(ctx, l);
	redraw_line(ctx, l);
}

void		down_key(t_ctx *ctx, t_line *l)
{
	update_histentry(ctx, l);
	ctx->hist.list = ctx->hist.list->prev;
	if (!ctx->hist.list->prev)
		l->line = l->lastline;
	else
		l->line = ft_dlstdup(T_HISTENTRY(ctx->hist.list->data)->line);
	clear_line(ctx, l);
	redraw_line(ctx, l);
}

void		lkey(t_ctx *ctx, t_line *l)
{
	move_cursor_backward(ctx, l);
	l->line = l->line->prev;
}

void		rkey(t_ctx *ctx, t_line *l)
{
	move_cursor_forward(ctx, l);
	l->line = l->line->next;
}
