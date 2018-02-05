/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 17:42:27 by lportay           #+#    #+#             */
/*   Updated: 2018/02/05 18:06:02 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Clear the line, print the prompt and will eventually update the history entry
*/

static void	load_histentry(t_21sh *env, t_line *l)
{
	clear_line(env, l);
	l->cursor_offset = 0;
	print_prompt(env);
	l->line_len = l->cursor_offset;
	if (l->line)
		ft_dlsthead(&l->line);
	if (env->hist.list->previous && l->line && l->line != l->lastline)
	{
		ft_dlstdel(&T_HISTENTRY(env->hist.list->content)->line, &delvoid);
		T_HISTENTRY(env->hist.list->content)->line = l->line;
	}
}

/*
** These 2 functions will print the histentry before loading them to be changed.
** They're changed when the user do something else than scrolling with UP and
** and DOWN KEYS. (See `user_input' first condition which call `load_line')
*/

void	up_key(t_21sh *env, t_line *l)
{
	load_histentry(env, l);
	env->hist.list = env->hist.list->next;
	print_line_cursor_len(l, T_HISTENTRY(env->hist.list->content)->line->next);
	l->line = NULL;
	if (!(env->line.cursor_offset % env->ws.ws_col))
		tputs(env->tc.dow, 1, &ft_putchar_stdin);
}

void	down_key(t_21sh *env, t_line *l)
{
	load_histentry(env, l);
	env->hist.list = env->hist.list->previous;
	if (!env->hist.list->previous)
	{
		l->line = l->lastline;
		print_line_cursor_len(l, l->line->next);
		ft_dlstend(&l->line);
	}
	else
	{
		print_line_cursor_len(l, T_HISTENTRY(env->hist.list->content)->line->next);
		l->line = NULL;
	}
	if (!(l->cursor_offset % env->ws.ws_col))
		tputs(env->tc.dow, 1, &ft_putchar_stdin);
}
