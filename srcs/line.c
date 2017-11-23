/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 17:38:36 by lportay           #+#    #+#             */
/*   Updated: 2017/11/23 13:36:01 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"


#include <string.h>

static void	user_input(char *buf, t_21sh *env)
{
	if (ft_isprint(buf[0]))
	{
		write(STDOUT_FILENO, &buf[0], 1);
		ft_dlstinsert(env->line, ft_dlstnew(buf, 1));
		env->line = env->line->next;
	}
	else if (buf[0] == 0x7f && env->line->previous)
	{
		tputs(env->tc.le, 1, &ft_putchar_stdin);
		tputs(env->tc.dc, 1, &ft_putchar_stdin);
		ft_dlstremove(&env->line, &delvoid, false);
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
//	else if (!ft_strncmp(buf, "\033[A", 4))
		//	haut dans l'historique
//	else if (!ft_strncmp(buf, "\033[B", 4))
		// bas dans l'historique
//	else if (!ft_strncmp(buf, "\x12", 1))
		//	recherche dans l'historique
//	else if (!ft_strncmp(buf, "\x23", 1))
//		write(STDOUT_FILENO, "CTRL-W\n", 8);
//	else if (!ft_strncmp(buf, "\t", 1))
		//	autocompletion
}

void	lineread(t_21sh *env)
{
	char buf[4];

	print_prompt(env);
	env->line = ft_dlstnew("HEAD", 5);
	tputs(env->tc.im, 1, &ft_putchar_stdin);//insert mode
	while(1)
	{
		ft_bzero(buf, 4);
		if (read(STDIN_FILENO, buf, 4) == -1 || buf[0] ==  '\n' ||
			(buf[0] == 4 && ft_dlstcount(env->line) == 0))
			break ;
		user_input(buf, env);
	}
	tputs(env->tc.ei, 1, &ft_putchar_stdin);//exit insert mode
	
	if (buf[0] == 0)
		fatal_err(FAILREAD, env);
	else if (buf[0] == 4)
		wrap_exit(EXIT_SUCCESS, env);
	ft_dlsthead(&env->line);
	
	write(1, "\n", 1);//
	ft_dlstprint(env->line->next, "");//
	ft_dlstdel(&env->line, &delvoid);////
	write(1, "\n", 1);//
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
