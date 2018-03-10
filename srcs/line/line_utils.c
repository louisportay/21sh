/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 19:02:58 by lportay           #+#    #+#             */
/*   Updated: 2018/03/10 20:40:18 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	add_newline(t_line *l)
{
	if ((l->linestate->state & (SQUOTE | DQUOTE) && !l->heredoc) ||
		 (l->linestate->state & HEREDOC))
		ft_dlstaddend(l->split_line, ft_dlstnew("\n", 1));
}

void	toggle_emacs_mode(t_ctx *ctx, t_line *l)
{
	(void)l;
	ctx->emacs_mode = !ctx->emacs_mode;	
}

void	lkey(t_ctx *ctx, t_line *l)
{
	move_cursor_backward(ctx, l);
	l->line = l->line->prev;
}

void	rkey(t_ctx *ctx, t_line *l)
{
	move_cursor_forward(ctx, l);
	l->line = l->line->next;
}
