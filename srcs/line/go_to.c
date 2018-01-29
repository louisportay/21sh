/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:10:46 by lportay           #+#    #+#             */
/*   Updated: 2018/01/26 14:34:54 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	go_upper_line(t_21sh *env)
{
	int excess_mov;

	tputs(env->line.tc.up, 1, &ft_putchar_stdin);
	env->line.cursor_offset -= env->line.ws.ws_col;
	excess_mov = move_dlst_head(&env->line.line, -env->line.ws.ws_col);
	if (excess_mov)
	{
		env->line.cursor_offset -= excess_mov;
		move_cursor_n_columns(-excess_mov);
	}
}

void	go_lower_line(t_21sh *env)
{
	int excess_mov;

	move_cursor_n_lines(1);
	env->line.cursor_offset += env->line.ws.ws_col;
	excess_mov = move_dlst_head(&env->line.line, env->line.ws.ws_col);
	if (excess_mov)
	{
		env->line.cursor_offset = env->line.line_len;
		move_cursor_n_columns(-excess_mov);
	}
}

void	go_to_line_beginning(t_21sh *env)
{
	int excess_mov;

	excess_mov = move_dlst_head(&env->line.line, -env->line.cursor_offset);
	while (env->line.cursor_line--)
		go_upper_line(env);
	tputs(env->line.tc.cr, 1, &ft_putchar_stdin);
	env->line.cursor_offset = -excess_mov;
	if (abs(excess_mov))
		move_cursor_n_columns(-excess_mov);
}

void	go_to_line_end(t_21sh *env)
{
	move_dlst_head(&env->line.line, env->line.line_len - env->line.cursor_offset);
	move_cursor_n_lines(env->line.num_lines - env->line.cursor_line);
	move_cursor_n_columns((env->line.line_len % env->line.ws.ws_col) - env->line.cursor_offset % env->line.ws.ws_col);
	env->line.cursor_offset = env->line.line_len;
}

void	go_to_previous_word(t_21sh *env)
{
	bool inword;

	inword = (ft_isalnum(*(char *)env->line.line->content) == true) ? true : false;
	while (inword == false && env->line.line->previous)
	{
		if (ft_isalnum(*(char *)env->line.line->content) == true)
			inword = true;
		lkey(env);
	}
	while (inword == true && env->line.line->previous)
	{
		if (ft_isalnum(*(char *)env->line.line->content) == false)
			break;
		lkey(env);
	}
}

void	go_to_next_word(t_21sh *env)
{
	bool inword;

	inword = (ft_isalnum(*(char *)env->line.line->next->content) == true) ? true : false;
	while (inword == false && env->line.line->next)
	{
		if (ft_isalnum(*(char *)env->line.line->next->content) == true)
		{
			inword = true;
			break;
		}
		rkey(env);
	}
	while (inword == true && env->line.line->next)
	{
		if (ft_isalnum(*(char *)env->line.line->next->content) == false)
			break;
		rkey(env);
	}
}
