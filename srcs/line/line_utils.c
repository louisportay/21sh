/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 19:02:58 by lportay           #+#    #+#             */
/*   Updated: 2018/03/06 20:39:47 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	add_newline(t_line *l)
{
	if ((l->linestate->state & (SQUOTE | DQUOTE) && !l->heredoc) ||
		 (l->linestate->state & HEREDOC))
		ft_dlstaddend(l->split_line, ft_dlstnew("\n", 1));
}

/*
** Copy current line from history
*/

void	load_line(t_ctx *ctx, t_line *l)
{
	l->line = ft_dlstdup(T_HISTENTRY(ctx->hist.list->data)->line);
	ft_dlstend(&l->line);
}

/*
** Maths.
** The state multiline is on when the cursor is not on the last line
*/

void	update_line(t_ctx *ctx, t_line *l)
{
	l->num_lines = l->line_len / ctx->ws.ws_col;
	l->cursor_line = l->cursor_offset / ctx->ws.ws_col;
//	if (l->multiline == true && (!l->line->next || 
//							//	l->line_len < ctx->ws.ws_col ||
//							//	l->line_len == l->cursor_offset || 
//								l->cursor_line == l->num_lines))
//		l->multiline = false;
//	else if (!l->multiline && l->cursor_line < l->num_lines)
//		l->multiline = true;
}

void	toggle_emacs_mode(t_ctx *ctx, t_line *l)
{
	(void)l;
	ctx->emacs_mode = !ctx->emacs_mode;	
}

static void handle_move_newline(t_ctx *ctx, t_line *l)
{
	t_dlist *tmp;
	int		offset;

	tmp = l->line->prev;
	tputs(ctx->tc.up, 1, &ft_putchar_stdin);	
	l->cursor_offset--;
	while (*(char *)tmp->data != '\n')
	{
		tputs(ctx->tc.nd, 1, &ft_putchar_stdin);
		tmp = tmp->prev;
		if (!tmp)
		{
			offset = l->cursor_offset - 1;
			while (--offset != 0)
				tputs(ctx->tc.nd, 1, &ft_putchar_stdin);
			break;
		}
	}

}

void	lkey(t_ctx *ctx, t_line *l)
{
	if (*(char *)l->line->data == '\n')
		handle_move_newline(ctx, l);
	else
		move_cursor_backward(ctx, l);
	l->line = l->line->prev;
}

void	rkey(t_ctx *ctx, t_line *l)
{
	if (l->line->next && *(char *)l->line->next->data == '\n')
	{
		l->cursor_offset++;
		tputs(ctx->tc.dow, 1, &ft_putchar_stdin);
	}
	else
		move_cursor_forward(ctx, l);
	l->line = l->line->next;
}
