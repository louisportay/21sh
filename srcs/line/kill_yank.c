/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_yank.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:48:21 by lportay           #+#    #+#             */
/*   Updated: 2018/01/26 14:33:08 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	kill_line_end(t_21sh *env)
{
	if (env->line.yank)
		ft_dlstdel(&env->line.yank, &delvoid);
	env->line.yank = env->line.line->next;
	env->line.line->next = NULL;
	env->line.yank->previous = NULL;
	env->line.line_len = env->line.cursor_offset;
	tputs(env->line.tc.cd, 1, &ft_putchar_stdin);
}

static void	print_rest_of_line(t_21sh *env)
{
	unsigned tmp;

	tmp = env->line.cursor_offset;
	tputs(env->line.tc.sc, 1, &ft_putchar_stdin);
	print_line_cursor(env, env->line.line->next);
	tputs(env->line.tc.rc, 1, &ft_putchar_stdin);
	env->line.line_len = env->line.cursor_offset;
	env->line.cursor_offset = tmp;
	if (!(env->line.cursor_offset % env->line.ws.ws_col))
		tputs(env->line.tc.dow, 1, &ft_putchar_stdin);
}

void	kill_line_beginning(t_21sh *env)
{
	t_dlist		*tmp;

	if (env->line.yank)
		ft_dlstdel(&env->line.yank, &delvoid);
	tmp = env->line.line->next;
	env->line.line->next = NULL;
	ft_dlsthead(&env->line.line);
	env->line.yank = env->line.line->next;
	env->line.yank->previous = NULL;
	env->line.line->next = tmp;
	if (tmp)
		tmp->previous = env->line.line;
	clear_line(env);
	env->line.cursor_offset = 0;
	print_prompt(env);
	print_rest_of_line(env);
}

void	kill_prev_word(t_21sh *env)
{
	t_dlist *tmp;

	if (env->line.yank)
		ft_dlstdel(&env->line.yank, &delvoid);
	tmp = env->line.line->next;
	env->line.line->next = NULL;
	if (tmp)
		tmp->previous = NULL;
	go_to_previous_word(env);
	env->line.yank = env->line.line->next;
	if (env->line.yank)
		env->line.yank->previous = NULL;
	env->line.line->next = tmp;
	if (tmp)
		tmp->previous = env->line.line;
	tputs(env->line.tc.cd, 1, &ft_putchar_stdin);
	print_rest_of_line(env);
}

void	yank(t_21sh *env)
{
	t_dlist *tmp;

	tmp = env->line.line->next;
	env->line.line->next = ft_dlstdup(env->line.yank);
	env->line.line->next->previous = env->line.line;
	tputs(env->line.tc.cd, 1, &ft_putchar_stdin);
	print_line_cursor_len(env, env->line.line->next);
	ft_dlstend(&env->line.line);
	env->line.line->next = tmp;
	if (tmp)
		tmp->previous = env->line.line;
	tputs(env->line.tc.sc, 1, &ft_putchar_stdin);
	print_line(env->line.line->next);
	tputs(env->line.tc.rc, 1, &ft_putchar_stdin);
	if (!(env->line.cursor_offset % env->line.ws.ws_col))
		tputs(env->line.tc.dow, 1, &ft_putchar_stdin);
}
