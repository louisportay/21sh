/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 19:10:15 by lportay           #+#    #+#             */
/*   Updated: 2017/12/09 17:44:38 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Function which print the right error message
*/

static void	dump_err(char errcode)
{
	t_keyval err[6];
	int 	i;

	err[0] = KEY_VAL(NOENVIRON, NOENVIRON_STR);
	err[1] = KEY_VAL(NOMEM, NOMEM_STR);
	err[2] = KEY_VAL(NODIR, NODIR_STR);
	err[3] = KEY_VAL(FAILSETSIGHDLR, FAILSETSIGHDLR_STR);
	err[4] = KEY_VAL(FAILREAD, FAILREAD_STR);
	err[5] = KEY_VAL(0, NULL);
	i = 0;
	while (errcode != err[i].key && err[i].key)
		i++;
	if (err[i].key)
		ft_putstr(err[i].val);
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
	if (env->line)
	//ft_dlsthead(&env->line);//
		ft_dlstdel(&env->line, &delvoid);
	if (env->histlist)//faire une fonction dédiée
	{
	////ft_dlsthead(&env->histlist);//
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
