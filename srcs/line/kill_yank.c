/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_yank.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:48:21 by lportay           #+#    #+#             */
/*   Updated: 2017/12/28 11:33:54 by lportay          ###   ########.fr       */
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

static void	print_rest_of_line(t_21sh *env)
{
	unsigned tmp;

	tmp = env->cursor_offset;
	tputs(env->tc.sc, 1, &ft_putchar_stdin);
	print_line_cursor(env, env->line->next);
	tputs(env->tc.rc, 1, &ft_putchar_stdin);
	env->line_len = env->cursor_offset;
	env->cursor_offset = tmp;
	if (!(env->cursor_offset % env->ws.ws_col))
		tputs(env->tc.dow, 1, &ft_putchar_stdin);
}

void	kill_line_beginning(t_21sh *env)
{
	t_dlist		*tmp;

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
	print_rest_of_line(env);
}

void	kill_prev_word(t_21sh *env)
{
	t_dlist *tmp;

	if (env->yank)
		ft_dlstdel(&env->yank, &delvoid);
	tmp = env->line->next;
	env->line->next = NULL;
	if (tmp)
		tmp->previous = NULL;
	go_to_previous_word(env);
	env->yank = env->line->next;
	if (env->yank)
		env->yank->previous = NULL;
	env->line->next = tmp;
	if (tmp)
		tmp->previous = env->line;
	tputs(env->tc.cd, 1, &ft_putchar_stdin);
	print_rest_of_line(env);
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
