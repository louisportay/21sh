/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 19:10:15 by lportay           #+#    #+#             */
/*   Updated: 2017/12/05 13:13:54 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Function which print the right error message
*/

static void	dump_err(char errcode)
{
	t_error	err[] = {
		{NOENVIRON, NOENVIRON_STR},
		{NOWINDOW, NOWINDOW_STR},
		{FAILSETENV, FAILSETENV_STR},
		{FAILSETLOCAL, FAILSETLOCAL_STR},
		{FAILSETSIGHDLR, FAILSETSIGHDLR_STR},
		{FAILREAD, FAILREAD_STR},
		{NODIR, NODIR_STR},
		{NOMEM, NOMEM_STR},
		{0, NULL}
	};
	int 	i;

	i = 0;
	while (errcode != err[i].errno && err[i].errno)
		i++;
	if (err[i].errno)
		ft_putstr(err[i].errmessage);
}

/*
** Print the error message and exit
*/

void		fatal_err(char errcode, t_21sh *env)
{
	dump_err(errcode);
	wrap_exit(EXIT_FAILURE, env);
}

void	wrap_exit(int status, t_21sh *env)
{
	//ft_dlsthead(&env->line);//
	if (env->line)
		ft_dlstdel(&env->line, &delvoid);
	if (env->histlist)//faire une fonction dédiée
	{
	//	ft_dlsthead(&env->histlist);//
		if (env->histlist->next)
		{
			trim_history(&env->histlist->next, hashlookup(env->localvar, "HISTFILESIZE"));
			save_history(env->localvar, env->histlist->next);
			env->histlist = env->histlist->next;
			ft_dlstdelone(&env->histlist->previous, &delvoid);
			ft_dlstdel(&env->histlist, &del_histentry);
		}
		else
			ft_dlstdelone(&env->histlist, &delvoid);
	}
	if (env->environ)
	{
		del_array((void **)env->environ);
		free(env->environ);
		env->environ = NULL;
	}
	hashclear(env->localvar, ft_memdel);
	write(STDOUT_FILENO, "exit\n", 6);
	if (env->line_edition == true)
		tcsetattr(STDIN_FILENO, TCSADRAIN, &env->oldtios);	
	exit(status);
}
