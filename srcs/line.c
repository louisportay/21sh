/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 17:38:36 by lportay           #+#    #+#             */
/*   Updated: 2017/12/14 13:03:38 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	move_cursor_n_columns(int n)
{
	char *tmp;

	if (!n)
		return ;
	write(STDIN_FILENO, ESC"[", 2);
	tmp = ft_itoa(abs(n));
	ft_putstr_fd(STDIN_FILENO, tmp);
	if (n > 0)
		write(STDIN_FILENO, "C", 1);
	else if (n < 0)
		write(STDIN_FILENO, "D", 1);
	free(tmp);
}

void	move_cursor_n_lines(int n)
{
	char *tmp;

	if (!n)
		return ;
	write(STDIN_FILENO, ESC"[", 2);
	tmp = ft_itoa(abs(n));
	ft_putstr_fd(STDIN_FILENO, tmp);
	if (n > 0)
		write(STDIN_FILENO, "B", 1);
	else if (n < 0)
		write(STDIN_FILENO, "A", 1);
	free(tmp);
}

void clear_line(t_21sh *env)
{
	tputs(env->tc.cr, 1, &ft_putchar_stdin);
	move_cursor_n_lines(-env->cursor_line);
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

static void	print_line_again(t_21sh *env, t_dlist *list)
{
	while (list)
	{
		env->cursor_offset++;
		write(STDOUT_FILENO, list->content, 1);
		list = list->next;
	}
}

static void	print_rest_of_line(t_dlist *list)
{
	while (list)
	{
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
	if (!(env->cursor_offset % env->ws.ws_col))
		tputs(env->tc.dow, 1, &ft_putchar_stdin);
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
	if (!(env->cursor_offset % env->ws.ws_col))
		tputs(env->tc.dow, 1, &ft_putchar_stdin);
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
	if (!(env->cursor_offset % env->ws.ws_col))
		tputs(env->tc.dow, 1, &ft_putchar_stdin);
}

void	move_cursor_forward(t_21sh *env)
{
		env->cursor_offset++;
		if (!(env->cursor_offset % env->ws.ws_col))
			tputs(env->tc.dow, 1, &ft_putchar_stdin);
		else
			tputs(env->tc.nd, 1, &ft_putchar_stdin);
}

void	move_cursor_backward(t_21sh *env)
{
	if (!(env->cursor_offset % env->ws.ws_col))
	{
		tputs(env->tc.up, 1, &ft_putchar_stdin);
		move_cursor_n_columns(env->ws.ws_col);		
	}
	else
		tputs(env->tc.le, 1, &ft_putchar_stdin);
	env->cursor_offset--;
}

void	insert_char_multiline(char *buf, t_21sh *env)
{
	tputs(env->tc.cd, 1, &ft_putchar_stdin);
	tputs(env->tc.sc, 1, &ft_putchar_stdin);
	env->line_len++;
	ft_dlstinsert(env->line, ft_dlstnew(buf, 1));
	env->line = env->line->next;
	print_rest_of_line(env->line);
	tputs(env->tc.rc, 1, &ft_putchar_stdin);
	move_cursor_forward(env);
}

void	go_upper_line(t_21sh *env)
{
	int excess_mov;

	tputs(env->tc.up, 1, &ft_putchar_stdin);
	env->cursor_offset -= env->ws.ws_col;
	excess_mov = move_dlst_head(&env->line, -env->ws.ws_col);
	if (excess_mov)
	{
		env->cursor_offset -= excess_mov;
		move_cursor_n_columns(-excess_mov);
	}
}

void	go_lower_line(t_21sh *env)
{
	int excess_mov;

	move_cursor_n_lines(1);
	env->cursor_offset += env->ws.ws_col;
	excess_mov = move_dlst_head(&env->line, env->ws.ws_col);
	if (excess_mov)
	{
		env->cursor_offset = env->line_len;
		move_cursor_n_columns(-excess_mov);
	}
}

void	load_line(t_21sh *env)
{
	env->line = ft_dlstdup(T_HISTENTRY(env->histlist->content)->line);
	ft_dlstend(&env->line);
}

void	update_linemode(t_21sh *env)
{
	env->num_lines = env->line_len / env->ws.ws_col;
	env->cursor_line = env->cursor_offset / env->ws.ws_col;
	if (env->multiline == true && (env->line_len < env->ws.ws_col || env->line_len == env->cursor_offset || env->cursor_line == env->num_lines))
		env->multiline = false;
	else if (env->multiline == false && env->cursor_line < env->num_lines)
		env->multiline = true;
}

//Hello

void	del_char_multiline(t_21sh *env, bool flag)
{
	(void)env;
	(void)flag;
}

void	del_char(t_21sh *env, bool flag)
{
	if (env->multiline)
		return (del_char_multiline(env, flag));
	if (flag == PREVIOUS)
		move_cursor_backward(env);
	else if (flag == CURRENT)
		env->line = env->line->next;
	env->line_len--;
	tputs(env->tc.dc, 1, &ft_putchar_stdin);
	ft_dlstremove(&env->line, &delvoid);
}

/*
** HUGE switch for user input
*/

static int	user_input(char *buf, t_21sh *env)
{
	update_linemode(env);
	if (env->emacs_mode)
	{
		if (ft_strncmp(buf, UP_KEY, 4) && ft_strncmp(buf, DOWN_KEY, 4) && *buf != C_P && *buf != C_N && !env->line)
			load_line(env);
	}
	else if (ft_strncmp(buf, UP_KEY, 4) && ft_strncmp(buf, DOWN_KEY, 4) && !env->line)
		load_line(env);

	if (*buf == RETURN || (env->emacs_mode && *buf == C_O))
	{
		if (env->line && ft_dlstaddr(env->line, 0) != env->lastline)
			ft_dlstdel(&env->lastline, &delvoid);
		return (FINISHREAD);
	}
	else if (*buf == C_D)
	{
		if (!ft_dlstcount(env->line))
			return (EXITSHELL);
		else if (env->emacs_mode && env->line->next)
				del_char(env, CURRENT);
	}
//	else if (*buf == '@')		//dump some information
//		tputs(env->tc.dow, 1, &ft_putchar_stdin);
//	{
//		printf("\n");
//		printf("line_len %zu\n", env->line_len);
//		printf("cursor_offset %zu\n", env->cursor_offset);
//		printf("ws_col %d\n", env->ws.ws_col);
//		printf("multiline %d\n", env->multiline);
//	}
	else if (*buf == C_L && env->emacs_mode)
	{
		tputs(env->tc.cl, 1, &ft_putchar_stdin);
		redraw_line(env);
	}
	else if (ft_isprint(*buf) && env->multiline == false)
	{
		write(STDOUT_FILENO, &(*buf), 1);
		tputs(env->tc.le, 1, &ft_putchar_stdin);
		move_cursor_forward(env);
		env->line_len++;
		ft_dlstinsert(env->line, ft_dlstnew(buf, 1));
		env->line = env->line->next;
	}
	else if (ft_isprint(*buf) && env->multiline == true)
		insert_char_multiline(buf, env);
	else if (*buf == DEL && env->line->previous) //add other keystrokes to delete
			del_char(env, PREVIOUS);
	else if ((!ft_strncmp(buf, LEFT_KEY, 4) || (*buf == C_B && env->emacs_mode)) && env->line->previous)
	{
		move_cursor_backward(env);
		env->line = env->line->previous;
	}
	else if ((!ft_strncmp(buf, RIGHT_KEY, 4) || (*buf == C_F && env->emacs_mode)) && env->line->next)
	{
		move_cursor_forward(env);
		env->line = env->line->next;
	}
	else if ((!ft_strncmp(buf, UP_KEY, 4) || (*buf == C_P && env->emacs_mode)) && env->histlist->next)
		up_key(env);
	else if ((!ft_strncmp(buf, DOWN_KEY, 4) || (*buf == C_N && env->emacs_mode)) && env->histlist->previous)
		down_key(env);
	else if (!ft_strncmp(buf, C_UP, 6) && (env->cursor_offset >= env->ws.ws_col))
		go_upper_line(env);
	else if (!ft_strncmp(buf, C_DOWN, 6) && (env->cursor_line < env->num_lines))
		go_lower_line(env);

// implem le ctrl-A
// ctrl-e

//	else if (*buf == C_MAGICKEY)
//		env->emacs_mode = !env->emacs_mode;


//	else if (*buf == C_R)
//		recherche dans l'historique
//	else if (!ft_strncmp(buf, "\x23", 1))
//		write(STDOUT_FILENO, "C-W\n", 8);
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

void	move_cursor_end_of_line(t_21sh *env)
{
	move_cursor_n_lines(env->num_lines - env->cursor_line);
	tputs(env->tc.cr, 1, &ft_putchar_stdin);
	move_cursor_n_columns(env->line_len % env->ws.ws_col);
}

//change lineread return *eventually*

void		lineread(t_21sh *env)
{
	int		status;
	char	buf[READBUF];

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
		ft_bzero(buf, READBUF);
		if (read(STDIN_FILENO, buf, READBUF) == -1)
			status = READERROR;
		else
			status = user_input(buf, env);
	}
	tputs(env->tc.ei, 1, &ft_putchar_stdin);
	if (env->multiline == true)
		move_cursor_end_of_line(env);

	if (env->histlist)
		ft_dlsthead(&env->histlist);
	ft_dlsthead(&env->line);

	if (status == READERROR)
		fatal_err(FAILREAD, env);
	else if (status == EXITSHELL)
		wrap_exit(EXIT_SUCCESS, env);
//		return (EXIT_SUCCESS);
//	else if (status == FINISHREAD)
//		add_histentry(env);
//	 	return (FINISHREAD);
//	we're all done! add histentry and return

	//DEBUG//
	write(1, "\n", 1);//
	print_line(env, env->line->next);//print what's retrieved
	write(1, "\n", 1);//
	/////////

	add_histentry(env);
}
