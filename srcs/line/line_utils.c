/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 19:02:58 by lportay           #+#    #+#             */
/*   Updated: 2018/01/29 20:33:59 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	load_line(t_21sh *env)
{
	env->line.line = ft_dlstdup(T_HISTENTRY(env->hist.list->content)->line);
	ft_dlstend(&env->line.line);
}

/*
** The state multiline is on when the cursor is not on the last line
*/

void	update_linemode(t_line *line)
{
	line->num_lines = line->line_len / line->ws.ws_col;
	line->cursor_line = line->cursor_offset / line->ws.ws_col;
	if (line->multiline == true && (!line->line->next || line->line_len < line->ws.ws_col || line->line_len == line->cursor_offset || line->cursor_line == line->num_lines))
		line->multiline = false;
	else if (line->multiline == false && line->cursor_line < line->num_lines)
		line->multiline = true;
}

void	reverse_emacs_mode(t_21sh *env)
{
	env->emacs_mode = !env->emacs_mode;	
}

void	lkey(t_21sh *env)
{
	move_cursor_backward(env);
	env->line.line = env->line.line->previous;
}

void	rkey(t_21sh *env)
{
	move_cursor_forward(env);
	env->line.line = env->line.line->next;
}
