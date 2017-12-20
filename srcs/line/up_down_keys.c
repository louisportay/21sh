/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 17:42:27 by lportay           #+#    #+#             */
/*   Updated: 2017/12/19 18:40:06 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Clear the line, print the prompt and will eventually update the history entry
*/

static void	load_histentry(t_21sh *env)
{
	clear_line(env);
	env->cursor_offset = 0;
	print_prompt(env);
	env->line_len = env->cursor_offset;
	if (env->line)
		ft_dlsthead(&env->line);
	if (env->histlist->previous && env->line && env->line != env->lastline)
	{
		ft_dlstdel(&T_HISTENTRY(env->histlist->content)->line, &delvoid);
		T_HISTENTRY(env->histlist->content)->line = env->line;
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
	env->histlist = env->histlist->next;
	print_line_cursor_len(env, T_HISTENTRY(env->histlist->content)->line->next);
	env->line = NULL;
	if (!(env->cursor_offset % env->ws.ws_col))
		tputs(env->tc.dow, 1, &ft_putchar_stdin);
}

void	down_key(t_21sh *env)
{
	load_histentry(env);
	env->histlist = env->histlist->previous;
	if (!env->histlist->previous)
	{
		env->line = env->lastline;
		print_line_cursor_len(env, env->line->next);
		ft_dlstend(&env->line);
	}
	else
	{
		print_line_cursor_len(env, T_HISTENTRY(env->histlist->content)->line->next);
		env->line = NULL;
	}
	if (!(env->cursor_offset % env->ws.ws_col))
		tputs(env->tc.dow, 1, &ft_putchar_stdin);
}
