/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 17:38:36 by lportay           #+#    #+#             */
/*   Updated: 2017/12/12 23:13:12 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void clear_line(t_21sh *env)
{
	unsigned n_lines;

	n_lines = env->cursor_offset  / env->ws.ws_col;
	tputs(env->tc.cr, 1, &ft_putchar_stdin);
	while (n_lines)
	{
		tputs(env->tc.up, 1, &ft_putchar_stdin);
		n_lines--;
	}
	tputs(env->tc.cd, 1, &ft_putchar_stdin);
}

static void	print_line(t_21sh *env, t_dlist *list)
{
	while (list)
	{
		env->cursor_offset++;
		env->line_len++;
		write(STDOUT_FILENO, list->content, 1);
		list = list->next;
	}
}

void	begin_newline(t_21sh *env)
{
	tputs(env->tc.cr, 1, &ft_putchar_stdin);
	tputs(env->tc.dow, 1, &ft_putchar_stdin);
}

static void	print_line_again(t_21sh *env, t_dlist *list)
{
	while (list)
	{
		env->cursor_offset++;
		write(STDOUT_FILENO, list->content, 1);
		list = list->next;
	}
}

/*
** Called when the window size changes and for CTRL-L trigger
*/

void	redraw_line(t_21sh *env)
{
	env->cursor_offset = 0;
	print_prompt(env);
	if (env->line)
	{
		ft_dlsthead(&env->line);
		print_line_again(env, env->line->next);
		ft_dlstend(&env->line);
	}
	else
		print_line_again(env, T_HISTENTRY(env->histlist->content)->line->next);
	if (env->line_len == env->ws.ws_col)
		begin_newline(env);
}

/*
** These 2 functions will print the histentry before loading them to be changed.
** They're changed when the user do something else than scrolling with UP and
** and DOWN KEYS. (See `user_input' first condition)
** It will update the current history entry if it has been changed and if the
** return key has not been pressed (and if UP_KEY or DOWN_KEY has been triggered
*/
 
static void	up_key(t_21sh *env)
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
	env->histlist = env->histlist->next;
	print_line(env, T_HISTENTRY(env->histlist->content)->line->next);
	if (env->line_len == env->ws.ws_col)
		begin_newline(env);
	env->line = NULL;
}

static void	down_key(t_21sh *env)
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
	env->histlist = env->histlist->previous;
	if (!env->histlist->previous)
	{
		env->line = env->lastline;
		print_line(env, env->line->next);
		ft_dlstend(&env->line);
	}
	else
	{
		print_line(env, T_HISTENTRY(env->histlist->content)->line->next);
		env->line = NULL;
	}
	if (env->line_len == env->ws.ws_col)
		begin_newline(env);
}

void	move_cursor_forward(t_21sh *env)
{
		env->cursor_offset++;
		if (!(env->cursor_offset % env->ws.ws_col))
			begin_newline(env);
		else
			tputs(env->tc.nd, 1, &ft_putchar_stdin);
}

void	move_cursor_backward(t_21sh *env)
{
	char *tmp;

	if (!(env->cursor_offset % env->ws.ws_col))
	{
		tputs(env->tc.up, 1, &ft_putchar_stdin);
		write(STDIN_FILENO, ESC"[", 2);
		tmp = ft_itoa(env->ws.ws_col);
		ft_putstr_fd(STDIN_FILENO, tmp);
		write(STDIN_FILENO, "C", 1);
		free(tmp);
	}
	else
		tputs(env->tc.le, 1, &ft_putchar_stdin);
	env->cursor_offset--;
}

/*
** HUGE switch for user input
*/

static int	user_input(char *buf, t_21sh *env)
{
	if (ft_strncmp(buf, UP_KEY, 4) && ft_strncmp(buf, DOWN_KEY, 4) && !env->line)
	{
		env->line = ft_dlstdup(T_HISTENTRY(env->histlist->content)->line);
		ft_dlstend(&env->line);
	}
	if (*buf == RETURN)
	{
		if (env->line && ft_dlstaddr(env->line, 0) != env->lastline)
			ft_dlstdel(&env->lastline, &delvoid);
		return (FINISHREAD);
	}
	else if (*buf == EOT && !ft_dlstcount(env->line))
		return (EXITSHELL);
//	else if (*buf == '@')		//dump some information
//	{
//		if (env->multiline == true)
//			DEBUG;
//		printf("line_len %zu\n", env->line_len);
//		printf("ws_col %d\n", env->ws.ws_col);
//		printf("\n\noffset = %zu\nrow =%zu\ncol = %zu\nSYSCOL = %d\n", env->cursor_offset, env->cursor_offset / env->ws.ws_col, env->cursor_offset % env->ws.ws_col, env->ws.ws_col);
	//	printf("%d\n", env->ws.ws_col);
//	}
	else if (*buf == CTRL_L)
	{
		tputs(env->tc.cl, 1, &ft_putchar_stdin);
		redraw_line(env);
	}
	else if (ft_isprint(*buf))
	{
		write(STDOUT_FILENO, &(*buf), 1);
		tputs(env->tc.le, 1, &ft_putchar_stdin);
		move_cursor_forward(env);
		env->line_len++;
		ft_dlstinsert(env->line, ft_dlstnew(buf, 1));
		env->line = env->line->next;
	}
	else if (*buf == DEL && env->line->previous)
	{
		move_cursor_backward(env);
		env->line_len--;
		tputs(env->tc.dc, 1, &ft_putchar_stdin);
		ft_dlstremove(&env->line, &delvoid);
	}
	else if (!ft_strncmp(buf, LEFT_KEY, 4) && env->line->previous)
	{
		move_cursor_backward(env);
		env->line = env->line->previous;
	}
	else if (!ft_strncmp(buf, RIGHT_KEY, 4) && env->line->next)
	{
		move_cursor_forward(env);
		env->line = env->line->next;
	}
	else if (!ft_strncmp(buf, UP_KEY, 4) && env->histlist->next)
		up_key(env);
	else if (!ft_strncmp(buf, DOWN_KEY, 4) && env->histlist->previous)
		down_key(env);

//	else if (!ft_strncmp(buf, "\x12", 1))
		//	recherche dans l'historique
//	else if (!ft_strncmp(buf, "\x23", 1))
//		write(STDOUT_FILENO, "CTRL-W\n", 8);
//	else if (!ft_strncmp(buf, "\t", 1))
		//	autocompletion

	return (READON);
}

static void	add_histentry(t_21sh *env)
{
	if (env->line->next)
	{
		ft_dlstinsert(env->histlist, ft_dlstnewaddr(new_histentry(env->line, env->histindex++), sizeof(t_histentry *)));
		trim_history(&env->histlist->next, hashlookup(env->localvar, "HISTSIZE"));
	}
	else
		ft_dlstdel(&env->line, &delvoid);
}

void	update_linemode(t_21sh *env)
{
	if (env->multiline == true && env->line_len < env->ws.ws_col)
		env->multiline = false;
	else if (env->multiline == false && env->line_len >= env->ws.ws_col)
		env->multiline = true;
}

void	lineread(t_21sh *env)
{
	int		status;
	char	buf[4];

	status = READON;
	env->line = ft_dlstnew("HEAD", 5);
	env->lastline = env->line;
	env->cursor_offset = 0;
	env->multiline = false;
	print_prompt(env);
	env->line_len = env->cursor_offset;

	tputs(env->tc.im, 1, &ft_putchar_stdin);
	while (status == READON)
	{
		update_linemode(env);
		ft_bzero(buf, 4);
		if (read(STDIN_FILENO, buf, 4) == -1)
			status = READERROR;
		else
			status = user_input(buf, env);
	}
	tputs(env->tc.ei, 1, &ft_putchar_stdin);

	if (env->histlist)
		ft_dlsthead(&env->histlist);
	ft_dlsthead(&env->line);

	if (status == READERROR)
		fatal_err(FAILREAD, env);
	else if (status == EXITSHELL)
		wrap_exit(EXIT_SUCCESS, env);
//	else if (status == FINISHREAD)
//		we're all done! add histentry and return

	//DEBUG//
	write(1, "\n", 1);//
	print_line(env, env->line->next);//print what's retrieved
	write(1, "\n", 1);//
	/////////

	add_histentry(env);
}
