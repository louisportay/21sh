/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 17:38:36 by lportay           #+#    #+#             */
/*   Updated: 2017/12/05 13:57:05 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

//static void clear_line(t_21sh *env, t_dlist *line, int length)
//{
//	while (line->next)
//	{
//		tputs(env->tc.nd, 1, &ft_putchar_stdin);
//		line = line->next;
//	}
//	while (length)
//	{
//		tputs(env->tc.le, 1, &ft_putchar_stdin);
//		tputs(env->tc.dc, 1, &ft_putchar_stdin);
//		length--;
//	}
//}

static int	user_input(char *buf, t_21sh *env)
{
//	static t_dlist *cur_line = NULL;
//	int length;

//	if (ft_strncmp(buf, "\033[A", 4) && !env->line)// load the line to be modified
//	{
//		env->line = ft_dlstdup(T_HISTENTRY(env->histlist->content)->line);
//	}
	if (buf[0] == '\n')
	{
//		if (cur_line)
//		{
//			ft_dlsthead(&cur_line);
//			ft_dlstdel(&cur_line, &delvoid);
//		}
		return (FINISHREAD);
	}
	else if (buf[0] == 4 && ft_dlstcount(env->line) == 0)
		return (EXITSHELL);
	else if (ft_isprint(buf[0]))
	{
		write(STDOUT_FILENO, &buf[0], 1);
		ft_dlstinsert(env->line, ft_dlstnew(buf, 1));
		env->line = env->line->next;
	}
	else if (buf[0] == 0x7f && env->line->previous)
	{
		tputs(env->tc.le, 1, &ft_putchar_stdin);
		tputs(env->tc.dc, 1, &ft_putchar_stdin);
		ft_dlstremove(&env->line, &delvoid);
	}
	else if (!ft_strncmp(buf, "\033[D", 4) && env->line->previous)
	{
		tputs(env->tc.le, 1, &ft_putchar_stdin);
		env->line = env->line->previous;
	}
	else if (!ft_strncmp(buf, "\033[C", 4) && env->line->next)
	{
		tputs(env->tc.nd, 1, &ft_putchar_stdin);
		env->line = env->line->next;
	}
/****************** FLECHE HAUT *****************/
//	else if (!ft_strncmp(buf, "\033[A", 4) && env->histlist->next)
//	{
//	while (line->next)
//	{
//		tputs(env->tc.nd, 1, &ft_putchar_stdin);
//		line = line->next;
//	}
//	length = ft_dlstcount(env->line);
//	while (length)
//	{
//		tputs(env->tc.le, 1, &ft_putchar_stdin);
//		tputs(env->tc.dc, 1, &ft_putchar_stdin);
//		length--;
//	}
//	//	if (env->line)
//	//		clear_line(env, env->line, ft_dlstcount(env->line));
//	//	else
//		//	clear_line(env, T_HISTENTRY(env->histlist->content)->line, ft_dlstcount(T_HISTENTRY(env->histlist->content)->line));
////		if (cur_line && env->line && cur_line != env->line)
////		{
////			//ft_dlstdel(&T_HISTENTRY(env->histlist->content)->line, &delvoid);
////			//T_HISTENTRY(env->histlist->content)->line = env->line;
////			ft_dlstdel(&env->line, &delvoid);//
////			env->line = NULL;
////		}
//		if (!cur_line)
//		{
//			cur_line = env->line;
//		//	env->line = NULL;
//		}
//		else
//			env->histlist = env->histlist->next;
//		env->line = T_HISTENTRY(env->histlist->content)->line;//NULL;//ft_dlstnew("HEAD", 5);//T_HISTENTRY(env->histlist->content)->line;
//		ft_dlstprint(env->line);//T_HISTENTRY(env->histlist->content)->line->next, "");
////	//	ft_dlstend(&env->line);
//	}
/****************** FLECHE BAS *****************/
//	else if (!ft_strncmp(buf, "\033[B", 4) && (env->histlist->previous->previous))// || cur_line))
//	{
//	while (line->next)
//	{
//		tputs(env->tc.nd, 1, &ft_putchar_stdin);
//		line = line->next;
//	}
//	length = ft_dlstcount(env->line);
//	while (length)
//	{
//		tputs(env->tc.le, 1, &ft_putchar_stdin);
//		tputs(env->tc.dc, 1, &ft_putchar_stdin);
//		length--;
//	}
//	//	if (env->line)
//		//	clear_line(env, T_HISTENTRY(env->histlist->content)->line, ft_dlstcount(T_HISTENTRY(env->histlist->content)->line));
//		if (!ft_strcmp(env->histlist->previous->content, "HEAD"))
//		{
//			env->line = cur_line;
//			cur_line = NULL;
//		}
//		else 
//			env->histlist = env->histlist->previous;
//		if (env->line)
//			ft_dlstprint(env->line, "");
//		else
//			ft_dlstprint(T_HISTENTRY(env->histlist->content)->line->next, "");
//	}
	//supprimer cur_line si on redescnd tout en bas
//	else if (!ft_strncmp(buf, "\x12", 1))
		//	recherche dans l'historique
//	else if (!ft_strncmp(buf, "\x23", 1))
//		write(STDOUT_FILENO, "CTRL-W\n", 8);
//	else if (!ft_strncmp(buf, "\t", 1))
		//	autocompletion
	return (READON);
}

void	lineread(t_21sh *env)
{
	int		status;
	char	buf[4];

	status = READON;
	print_prompt(env);
	env->line = ft_dlstnew("HEAD", 5);

//	if (env->histlist->next)
//		env->histlist = env->histlist->next;//skip HEAD

	tputs(env->tc.im, 1, &ft_putchar_stdin);//insert mode
	while (status == READON)
	{
		ft_bzero(buf, 4);
		if (read(STDIN_FILENO, buf, 4) == -1)
			status = READERROR;
		else
			status = user_input(buf, env);
	}
	tputs(env->tc.ei, 1, &ft_putchar_stdin);//exit insert mode

//	if (env->histlist)
//		ft_dlsthead(&env->histlist);//~
//	if (env->line)
		ft_dlsthead(&env->line);//

	if (status == READERROR)
		fatal_err(FAILREAD, env);
	else if (status == EXITSHELL)
		wrap_exit(EXIT_SUCCESS, env);
//	else if (status == FINISHREAD)
//		we're all done!

	write(1, "\n", 1);//
//	if (env->line)//
		ft_dlstprint(env->line->next, "");//print what's retrieved
	write(1, "\n", 1);//
	
//	if (env->line->next)
//	{
//		ft_dlstinsert(env->histlist, ft_dlstnewaddr(new_histentry(env->line, env->histindex++), sizeof(t_histentry *)));
//		trim_history(&env->histlist->next, hashlookup(env->localvar, "HISTSIZE"));
//		write(1, "\n", 1);//
//		dump_history(env->histlist->next);//
//	}
//	else
		ft_dlstdel(&env->line, &delvoid);//
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

	write(1, "\n", 1);//
	ft_dlstprint(env->line->next, "");//
	ft_dlstdel(&env->line, &delvoid);////
	write(1, "\n", 1);//
}
