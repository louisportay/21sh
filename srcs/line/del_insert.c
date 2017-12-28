/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:44:52 by lportay           #+#    #+#             */
/*   Updated: 2017/12/27 15:17:41 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void del_char(t_21sh *env)
{
	env->line_len--;
	ft_dlstremove(&env->line, &delvoid);
	if (env->multiline)
	{
		tputs(env->tc.cd, 1, &ft_putchar_stdin);
		tputs(env->tc.sc, 1, &ft_putchar_stdin);
		print_line(env->line->next);
		tputs(env->tc.rc, 1, &ft_putchar_stdin);
	}
	else
		tputs(env->tc.dc, 1, &ft_putchar_stdin);
}
void	del_current_char(t_21sh *env)
{
	env->line = env->line->next;
	del_char(env);
}

void	del_previous_char(t_21sh *env)
{
	move_cursor_backward(env);
	env->cursor_line = env->cursor_offset / env->ws.ws_col;
	if (env->multiline == false && env->cursor_line < env->num_lines)
		env->multiline = true;
	del_char(env);
}

void	insert_char(char *buf, t_21sh *env)
{
	env->line_len++;
	env->num_lines = env->line_len / env->ws.ws_col;
	ft_dlstinsert(env->line, ft_dlstnew(buf, 1));
	env->line = env->line->next;
	if (env->multiline)
	{
		tputs(env->tc.cd, 1, &ft_putchar_stdin);
		print_line(env->line);
		if (!(env->line_len % env->ws.ws_col))
			tputs(env->tc.dow, 1, &ft_putchar_stdin);
		move_cursor_n_lines(-(env->num_lines - env->cursor_line));
		move_cursor_n_columns(env->cursor_offset % env->ws.ws_col - env->line_len % env->ws.ws_col);
	}
	else if (!env->multiline)
	{
		write(STDOUT_FILENO, buf, 1);
		tputs(env->tc.le, 1, &ft_putchar_stdin);
	}
	move_cursor_forward(env);
}
