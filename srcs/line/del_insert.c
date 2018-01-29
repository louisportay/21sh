/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 18:44:52 by lportay           #+#    #+#             */
/*   Updated: 2018/01/26 14:46:42 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void del_char(t_21sh *env)
{
	env->line.line_len--;
	ft_dlstremove(&env->line.line, &delvoid);
	if (env->line.multiline)
	{
		tputs(env->line.tc.cd, 1, &ft_putchar_stdin);
		tputs(env->line.tc.sc, 1, &ft_putchar_stdin);
		print_line(env->line.line->next);
		tputs(env->line.tc.rc, 1, &ft_putchar_stdin);
	}
	else
		tputs(env->line.tc.dc, 1, &ft_putchar_stdin);
}
void	del_current_char(t_21sh *env)
{
	env->line.line = env->line.line->next;
	del_char(env);
}

void	del_previous_char(t_21sh *env)
{
	move_cursor_backward(env);
	env->line.cursor_line = env->line.cursor_offset / env->line.ws.ws_col;
	if (env->line.multiline == false && env->line.cursor_line < env->line.num_lines)
		env->line.multiline = true;
	del_char(env);
}

void	insert_char(char *buf, t_21sh *env)
{
	env->line.line_len++;
	env->line.num_lines = env->line.line_len / env->line.ws.ws_col;
	ft_dlstinsert(env->line.line, ft_dlstnew(buf, 1));
	env->line.line = env->line.line->next;
	if (env->line.multiline)
	{
		tputs(env->line.tc.cd, 1, &ft_putchar_stdin);
		print_line(env->line.line);
		if (!(env->line.line_len % env->line.ws.ws_col))
			tputs(env->line.tc.dow, 1, &ft_putchar_stdin);
		move_cursor_n_lines(-(env->line.num_lines - env->line.cursor_line));
		move_cursor_n_columns(env->line.cursor_offset % env->line.ws.ws_col - env->line.line_len % env->line.ws.ws_col);
	}
	else if (!env->line.multiline)
	{
		write(STDOUT_FILENO, buf, 1);
		tputs(env->line.tc.le, 1, &ft_putchar_stdin);
	}
	move_cursor_forward(env);
}
