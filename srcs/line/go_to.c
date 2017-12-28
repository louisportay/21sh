/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:10:46 by lportay           #+#    #+#             */
/*   Updated: 2017/12/28 11:29:35 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	go_upper_line(t_21sh *env)
{
	int excess_mov;

	tputs(env->tc.up, 1, &ft_putchar_stdin);
	env->cursor_offset -= env->ws.ws_col;
	excess_mov = move_dlst_head(&env->line, -env->ws.ws_col);
	if (excess_mov)
	{
		env->cursor_offset -= excess_mov;
		move_cursor_n_columns(-excess_mov);
	}
}

void	go_lower_line(t_21sh *env)
{
	int excess_mov;

	move_cursor_n_lines(1);
	env->cursor_offset += env->ws.ws_col;
	excess_mov = move_dlst_head(&env->line, env->ws.ws_col);
	if (excess_mov)
	{
		env->cursor_offset = env->line_len;
		move_cursor_n_columns(-excess_mov);
	}
}

void	go_to_line_beginning(t_21sh *env)
{
	int excess_mov;

	excess_mov = move_dlst_head(&env->line, -env->cursor_offset);
	while (env->cursor_line--)
		go_upper_line(env);
	tputs(env->tc.cr, 1, &ft_putchar_stdin);
	env->cursor_offset = -excess_mov;
	if (abs(excess_mov))
		move_cursor_n_columns(-excess_mov);
}

void	go_to_line_end(t_21sh *env)
{
	move_dlst_head(&env->line, env->line_len - env->cursor_offset);
	move_cursor_n_lines(env->num_lines - env->cursor_line);
	move_cursor_n_columns((env->line_len % env->ws.ws_col) - env->cursor_offset % env->ws.ws_col);
	env->cursor_offset = env->line_len;
}

void	go_to_previous_word(t_21sh *env)
{
	bool inword;

	inword = (ft_isalnum(*(char *)env->line->content) == true) ? true : false;
	while (inword == false && env->line->previous)
	{
		if (ft_isalnum(*(char *)env->line->content) == true)
			inword = true;
		lkey(env);
	}
	while (inword == true && env->line->previous)
	{
		if (ft_isalnum(*(char *)env->line->content) == false)
			break;
		lkey(env);
	}
}

void	go_to_next_word(t_21sh *env)
{
	bool inword;

	inword = (ft_isalnum(*(char *)env->line->next->content) == true) ? true : false;
	while (inword == false && env->line->next)
	{
		if (ft_isalnum(*(char *)env->line->next->content) == true)
		{
			inword = true;
			break;
		}
		rkey(env);
	}
	while (inword == true && env->line->next)
	{
		if (ft_isalnum(*(char *)env->line->next->content) == false)
			break;
		rkey(env);
	}
}
