/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 17:42:27 by lportay           #+#    #+#             */
/*   Updated: 2018/01/26 15:00:05 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Clear the line, print the prompt and will eventually update the history entry
*/

static void	load_histentry(t_21sh *env)
{
	clear_line(env);
	env->line.cursor_offset = 0;
	print_prompt(env);
	env->line.line_len = env->line.cursor_offset;
	if (env->line.line)
		ft_dlsthead(&env->line.line);
	if (env->hist.list->previous && env->line.line && env->line.line != env->line.lastline)
	{
		ft_dlstdel(&T_HISTENTRY(env->hist.list->content)->line, &delvoid);
		T_HISTENTRY(env->hist.list->content)->line = env->line.line;
	}
}

/*
** These 2 functions will print the histentry before loading them to be changed.
** They're changed when the user do something else than scrolling with UP and
** and DOWN KEYS. (See `user_input' first condition which call `load_line')
*/

void	up_key(t_21sh *env)
{
	load_histentry(env);
	env->hist.list = env->hist.list->next;
	print_line_cursor_len(env, T_HISTENTRY(env->hist.list->content)->line->next);
	env->line.line = NULL;
	if (!(env->line.cursor_offset % env->line.ws.ws_col))
		tputs(env->line.tc.dow, 1, &ft_putchar_stdin);
}

void	down_key(t_21sh *env)
{
	load_histentry(env);
	env->hist.list = env->hist.list->previous;
	if (!env->hist.list->previous)
	{
		env->line.line = env->line.lastline;
		print_line_cursor_len(env, env->line.line->next);
		ft_dlstend(&env->line.line);
	}
	else
	{
		print_line_cursor_len(env, T_HISTENTRY(env->hist.list->content)->line->next);
		env->line.line = NULL;
	}
	if (!(env->line.cursor_offset % env->line.ws.ws_col))
		tputs(env->line.tc.dow, 1, &ft_putchar_stdin);
}
