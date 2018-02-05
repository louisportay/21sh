/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 19:02:58 by lportay           #+#    #+#             */
/*   Updated: 2018/02/05 22:03:32 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	load_line(t_21sh *env, t_line *l)
{
	l->line = ft_dlstdup(T_HISTENTRY(env->hist.list->content)->line);
	ft_dlstend(&l->line);
}

/*
** The state multiline is on when the cursor is not on the last line
*/

void	update_line(t_21sh *env, t_line *l)
{
	l->num_lines = l->line_len / env->ws.ws_col;
	l->cursor_line = l->cursor_offset / env->ws.ws_col;
	if (l->multiline == true && (!l->line->next || l->line_len < env->ws.ws_col ||
			l->line_len == l->cursor_offset || l->cursor_line == l->num_lines))
		l->multiline = false;
	else if (!l->multiline && l->cursor_line < l->num_lines)
		l->multiline = true;
}

void	reverse_emacs_mode(t_21sh *env, t_line *l)
{
	(void)l;
	env->emacs_mode = !env->emacs_mode;	
}

void	lkey(t_21sh *env, t_line *l)
{
	move_cursor_backward(env, l);
	l->line = l->line->previous;
}

void	rkey(t_21sh *env, t_line *l)
{
	move_cursor_forward(env, l);
	l->line = l->line->next;
}
