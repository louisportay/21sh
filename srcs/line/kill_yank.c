/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_yank.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:48:21 by lportay           #+#    #+#             */
/*   Updated: 2018/02/05 18:15:31 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	kill_line_end(t_21sh *env, t_line *l)
{
	if (l->yank)
		ft_dlstdel(&l->yank, &delvoid);
	l->yank = l->line->next;
	l->line->next = NULL;
	l->yank->previous = NULL;
	l->line_len = l->cursor_offset;
	tputs(env->tc.cd, 1, &ft_putchar_stdin);
}

static void	print_rest_of_line(t_21sh *env, t_line *l)
{
	unsigned tmp;

	tmp = l->cursor_offset;
	tputs(env->tc.sc, 1, &ft_putchar_stdin);
	print_line_cursor(l, l->line->next);
	tputs(env->tc.rc, 1, &ft_putchar_stdin);
	l->line_len = l->cursor_offset;
	l->cursor_offset = tmp;
	if (!(l->cursor_offset % env->ws.ws_col))
		tputs(env->tc.dow, 1, &ft_putchar_stdin);
}

void	kill_line_beginning(t_21sh *env, t_line *l)
{
	t_dlist		*tmp;

	if (l->yank)
		ft_dlstdel(&l->yank, &delvoid);
	tmp = l->line->next;
	l->line->next = NULL;
	ft_dlsthead(&l->line);
	l->yank = l->line->next;
	l->yank->previous = NULL;
	l->line->next = tmp;
	if (tmp)
		tmp->previous = l->line;
	clear_line(env, l);
	l->cursor_offset = 0;
	print_prompt(env);
	print_rest_of_line(env, l);
}

void	kill_prev_word(t_21sh *env, t_line *l)
{
	t_dlist *tmp;

	if (l->yank)
		ft_dlstdel(&l->yank, &delvoid);
	tmp = l->line->next;
	l->line->next = NULL;
	if (tmp)
		tmp->previous = NULL;
	go_to_previous_word(env, l);
	l->yank = l->line->next;
	if (l->yank)
		l->yank->previous = NULL;
	l->line->next = tmp;
	if (tmp)
		tmp->previous = l->line;
	tputs(env->tc.cd, 1, &ft_putchar_stdin);
	print_rest_of_line(env, l);
}

void	yank(t_21sh *env, t_line *l)
{
	t_dlist *tmp;

	tmp = l->line->next;
	l->line->next = ft_dlstdup(l->yank);
	l->line->next->previous = l->line;
	tputs(env->tc.cd, 1, &ft_putchar_stdin);
	print_line_cursor_len(l, l->line->next);
	ft_dlstend(&l->line);
	l->line->next = tmp;
	if (tmp)
		tmp->previous = l->line;
	tputs(env->tc.sc, 1, &ft_putchar_stdin);
	print_line(l->line->next);
	tputs(env->tc.rc, 1, &ft_putchar_stdin);
	if (!(l->cursor_offset % env->ws.ws_col))
		tputs(env->tc.dow, 1, &ft_putchar_stdin);
}
