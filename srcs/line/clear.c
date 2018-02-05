/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:52:05 by lportay           #+#    #+#             */
/*   Updated: 2018/02/05 18:16:40 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Called when the window size changes and for CTRL-L trigger
** Redraw the whole line with the prompt
*/

void	redraw_line(t_21sh *env, t_line *l)
{
	l->cursor_offset = 0;
	print_prompt(env);
	if (l->line)
	{
		ft_dlsthead(&l->line);
		print_line_cursor(l, l->line->next);
		ft_dlstend(&l->line);
	}
	else
		print_line_cursor(l, T_HISTENTRY(env->hist.list->content)->line->next);
	if (!(l->cursor_offset % env->ws.ws_col))
		tputs(env->tc.dow, 1, &ft_putchar_stdin);
}

void clear_line(t_21sh *env, t_line *l)
{
	tputs(env->tc.cr, 1, &ft_putchar_stdin);
	move_cursor_n_lines(-l->cursor_line);
	tputs(env->tc.cd, 1, &ft_putchar_stdin);
}

void	clear_screen_(t_21sh *env, t_line *l)
{
	tputs(env->tc.cl, 1, &ft_putchar_stdin);
	redraw_line(env, l);
}
