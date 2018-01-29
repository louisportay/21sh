/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:52:05 by lportay           #+#    #+#             */
/*   Updated: 2018/01/26 15:00:58 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Called when the window size changes and for CTRL-L trigger
** Redraw the whole line with the prompt
*/

void	redraw_line(t_21sh *env)
{
	env->line.cursor_offset = 0;
	print_prompt(env);
	if (env->line.line)
	{
		ft_dlsthead(&env->line.line);
		print_line_cursor(env, env->line.line->next);
		ft_dlstend(&env->line.line);
	}
	else
		print_line_cursor(env, T_HISTENTRY(env->hist.list->content)->line->next);
	if (!(env->line.cursor_offset % env->line.ws.ws_col))
		tputs(env->line.tc.dow, 1, &ft_putchar_stdin);
}

void clear_line(t_21sh *env)
{
	tputs(env->line.tc.cr, 1, &ft_putchar_stdin);
	move_cursor_n_lines(-env->line.cursor_line);
	tputs(env->line.tc.cd, 1, &ft_putchar_stdin);
}

void	clear_screen_(t_21sh *env)
{
	tputs(env->line.tc.cl, 1, &ft_putchar_stdin);
	redraw_line(env);
}
