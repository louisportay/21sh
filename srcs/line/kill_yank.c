/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_yank.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:48:21 by lportay           #+#    #+#             */
/*   Updated: 2017/12/19 18:48:47 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	kill_line_end(t_21sh *env)
{
	if (env->yank)
		ft_dlstdel(&env->yank, &delvoid);
	env->yank = env->line->next;
	env->line->next = NULL;
	env->yank->previous = NULL;
	env->line_len = env->cursor_offset;
	tputs(env->tc.cd, 1, &ft_putchar_stdin);
}

void	kill_line_beginning(t_21sh *env)
{
	t_dlist		*tmp;
	unsigned	prompt_offset;

	if (env->yank)
		ft_dlstdel(&env->yank, &delvoid);
	tmp = env->line->next;
	env->line->next = NULL;
	ft_dlsthead(&env->line);
	env->yank = env->line->next;
	env->yank->previous = NULL;
	env->line->next = tmp;
	if (tmp)
		tmp->previous = env->line;
	clear_line(env);
	env->cursor_offset = 0;
	print_prompt(env);
	prompt_offset = env->cursor_offset;
	tputs(env->tc.sc, 1, &ft_putchar_stdin);
	print_line_cursor(env, env->line->next);
	tputs(env->tc.rc, 1, &ft_putchar_stdin);
	env->line_len = env->cursor_offset;
	env->cursor_offset = prompt_offset;
	if (!(env->cursor_offset % env->ws.ws_col))
		tputs(env->tc.dow, 1, &ft_putchar_stdin);
}

void	yank(t_21sh *env)
{
	t_dlist *tmp;

	tmp = env->line->next;
	env->line->next = ft_dlstdup(env->yank);
	env->line->next->previous = env->line;
	tputs(env->tc.cd, 1, &ft_putchar_stdin);
	print_line_cursor_len(env, env->line->next);
	ft_dlstend(&env->line);
	env->line->next = tmp;
	if (tmp)
		tmp->previous = env->line;
	tputs(env->tc.sc, 1, &ft_putchar_stdin);
	print_line(env->line->next);
	tputs(env->tc.rc, 1, &ft_putchar_stdin);
	if (!(env->cursor_offset % env->ws.ws_col))
		tputs(env->tc.dow, 1, &ft_putchar_stdin);
}
