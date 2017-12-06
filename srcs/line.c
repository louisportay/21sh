/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 17:38:36 by lportay           #+#    #+#             */
/*   Updated: 2017/12/06 22:29:03 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void clear_line(t_21sh *env, t_dlist *line)
{
	int length;

	length = ft_dlstcount(line);
	change_cursor_offset(env, -length);
	while (length)
	{
		tputs(env->tc.le, 1, &ft_putchar_stdin);
		tputs(env->tc.dc, 1, &ft_putchar_stdin);
		length--;
	}
}

static void	wrap_clear_line(t_21sh *env)
{
	if (env->line)
	{
		while (env->line->next)
		{
			change_cursor_offset(env, 1);
			tputs(env->tc.nd, 1, &ft_putchar_stdin);
			env->line = env->line->next;
		}
		clear_line(env, env->line);
		ft_dlsthead(&env->line);
	}
	else
		clear_line(env, T_HISTENTRY(env->histlist->content)->line);
}

static void	print_line(t_21sh *env, t_dlist *list)
{
	while (list)
	{
		change_cursor_offset(env, 1);
		ft_putstr(list->content);
		list = list->next;
	}
}
/*
** first `if' --> Will modify the current history entry if the return key is not pressed
** and if up_key or down_key is triggered
*/

static void	up_key(t_21sh *env)
{
	wrap_clear_line(env);
	if (env->histlist->previous && env->line && env->line != env->lastline)
	{
		ft_dlstdel(&T_HISTENTRY(env->histlist->content)->line, &delvoid);
		T_HISTENTRY(env->histlist->content)->line = env->line;
	}
	env->histlist = env->histlist->next;
	print_line(env, T_HISTENTRY(env->histlist->content)->line->next);
	env->line = NULL;
}

static void	down_key(t_21sh *env)
{
	wrap_clear_line(env);
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
}

static int	user_input(char *buf, t_21sh *env)
{
	if (ft_strncmp(buf, UP_KEY, 4) && ft_strncmp(buf, DOWN_KEY, 4) && !env->line)
	{
		env->line = ft_dlstdup(T_HISTENTRY(env->histlist->content)->line);
		ft_dlstend(&env->line);
	}
	if (buf[0] == RETURN)
	{
		if (env->line && ft_dlstaddr(env->line, 0) != env->lastline)
			ft_dlstdel(&env->lastline, &delvoid);
		return (FINISHREAD);
	}
	else if (buf[0] == EOT && ft_dlstcount(env->line) == 0)
		return (EXITSHELL);
	else if (buf[0] == 'd')//dump some information
	{
//		tputs(tgetstr("up", NULL), 1, &ft_putchar_stdin);//go the line up
		printf("\n[0] =%d\n[1] = %d\n", env->cursor_offset[0], env->cursor_offset[1]);
	}
	else if (ft_isprint(buf[0]))
	{
		change_cursor_offset(env, 1);
		write(STDOUT_FILENO, &buf[0], 1);
		ft_dlstinsert(env->line, ft_dlstnew(buf, 1));
		env->line = env->line->next;
	}
	else if (buf[0] == DEL && env->line->previous)
	{
		change_cursor_offset(env, -1);
		tputs(env->tc.le, 1, &ft_putchar_stdin);
		tputs(env->tc.dc, 1, &ft_putchar_stdin);
		ft_dlstremove(&env->line, &delvoid);
	}
	else if (!ft_strncmp(buf, LEFT_KEY, 4) && env->line->previous)
	{
		if (env->cursor_offset[0] == 0 && env->cursor_offset[1] > 0)
		{
			env->cursor_offset[0] = env->ws.ws_col - 1;
			env->cursor_offset[1]--;
		}
		else
		{
			tputs(env->tc.le, 1, &ft_putchar_stdin);
			change_cursor_offset(env, -1);
		}
		env->line = env->line->previous;
	}
	else if (!ft_strncmp(buf, RIGHT_KEY, 4) && env->line->next)//modifier tout ca avec l'offset et tout
	{
		change_cursor_offset(env, 1);
		tputs(env->tc.nd, 1, &ft_putchar_stdin);
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

void	lineread(t_21sh *env)
{
	int		status;
	char	buf[4];

	status = READON;
	env->line = ft_dlstnew("HEAD", 5);
	env->lastline = env->line;
	env->cursor_offset[0] = 0;
	env->cursor_offset[1] = 0;

	print_prompt(env);
	tputs(env->tc.im, 1, &ft_putchar_stdin);
	while (status == READON)
	{
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
//		we're all done!

	//DEBUG//
	write(1, "\n", 1);//
	print_line(env, env->line->next);//print what's retrieved
	write(1, "\n", 1);//
	/////////
	add_histentry(env);
}

void	getrawline(t_21sh *env)
{
	char *tmp;

	print_prompt(env);
	if (get_next_line(STDIN_FILENO, &tmp) == -1)
		fatal_err(FAILREAD, env);
	if (!tmp)
		wrap_exit(EXIT_SUCCESS, env);
	env->line = str_to_dlst(tmp);
	ft_strdel(&tmp);

	//DEBUG//
	write(1, "\n", 1);//
	print_line(env, env->line->next);//
	write(1, "\n", 1);//
	/////////
	
	ft_dlstdel(&env->line, &delvoid);
}
