/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:52:05 by lportay           #+#    #+#             */
/*   Updated: 2017/12/19 18:53:34 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Called when the window size changes and for CTRL-L trigger
** Redraw the whole line with the prompt
*/

void	redraw_line(t_21sh *env)
{
	env->cursor_offset = 0;
	print_prompt(env);
	if (env->line)
	{
		ft_dlsthead(&env->line);
		print_line_cursor(env, env->line->next);
		ft_dlstend(&env->line);
	}
	else
		print_line_cursor(env, T_HISTENTRY(env->histlist->content)->line->next);
	if (!(env->cursor_offset % env->ws.ws_col))
		tputs(env->tc.dow, 1, &ft_putchar_stdin);
}

void clear_line(t_21sh *env)
{
	tputs(env->tc.cr, 1, &ft_putchar_stdin);
	move_cursor_n_lines(-env->cursor_line);
	tputs(env->tc.cd, 1, &ft_putchar_stdin);
}

void	clear_screen_(t_21sh *env)
{
	tputs(env->tc.cl, 1, &ft_putchar_stdin);
	redraw_line(env);
}
