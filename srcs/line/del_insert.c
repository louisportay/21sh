/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:44:52 by lportay           #+#    #+#             */
/*   Updated: 2018/02/05 22:05:20 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void del_char(t_21sh *env, t_line *l)
{
	l->line_len--;
	ft_dlstremove(&l->line, &delvoid);
	if (l->multiline)
	{
		tputs(env->tc.cd, 1, &ft_putchar_stdin);
		tputs(env->tc.sc, 1, &ft_putchar_stdin);
		print_line(l->line->next);
		tputs(env->tc.rc, 1, &ft_putchar_stdin);
	}
	else
		tputs(env->tc.dc, 1, &ft_putchar_stdin);
}
void	del_current_char(t_21sh *env, t_line *l)
{
	l->line = l->line->next;
	del_char(env, l);
}

void	del_previous_char(t_21sh *env, t_line *l)
{
	move_cursor_backward(env, l);
	l->cursor_line = l->cursor_offset / env->ws.ws_col;
	if (!l->multiline && l->cursor_line < l->num_lines)
		l->multiline = true;
	del_char(env, l);
}

void	insert_char(char *buf, t_21sh *env, t_line *l)
{
	l->line_len++;
	l->num_lines = l->line_len / env->ws.ws_col;
	ft_dlstinsert(l->line, ft_dlstnew(buf, 1));
	l->line = l->line->next;
	if (l->multiline)
	{
		tputs(env->tc.cd, 1, &ft_putchar_stdin);
		print_line(l->line);
		if (!(l->line_len % env->ws.ws_col))
			tputs(env->tc.dow, 1, &ft_putchar_stdin);
		move_cursor_n_lines(-(l->num_lines - l->cursor_line));
		move_cursor_n_columns(l->cursor_offset % env->ws.ws_col - l->line_len % env->ws.ws_col);
	}
	else if (!l->multiline)
	{
		write(STDOUT_FILENO, buf, 1);
		tputs(env->tc.le, 1, &ft_putchar_stdin);
	}
	move_cursor_forward(env, l);
}
