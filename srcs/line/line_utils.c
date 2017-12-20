/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 19:02:58 by lportay           #+#    #+#             */
/*   Updated: 2017/12/20 17:19:09 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	load_line(t_21sh *env)
{
	env->line = ft_dlstdup(T_HISTENTRY(env->histlist->content)->line);
	ft_dlstend(&env->line);
}

/*
** The state multiline is on when the cursor is not on the last line
*/

void	update_linemode(t_21sh *env)
{
	env->num_lines = env->line_len / env->ws.ws_col;
	env->cursor_line = env->cursor_offset / env->ws.ws_col;
	if (env->multiline == true && (env->line_len < env->ws.ws_col || env->line_len == env->cursor_offset || env->cursor_line == env->num_lines))
		env->multiline = false;
	else if (env->multiline == false && env->cursor_line < env->num_lines)
		env->multiline = true;
}

void	reverse_emacs_mode(t_21sh *env)
{
	env->emacs_mode = !env->emacs_mode;	
}

void	lkey(t_21sh *env)
{
	move_cursor_backward(env);
	env->line = env->line->previous;
}

void	rkey(t_21sh *env)
{
	move_cursor_forward(env);
	env->line = env->line->next;
}
