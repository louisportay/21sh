/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 19:10:15 by lportay           #+#    #+#             */
/*   Updated: 2017/11/23 13:21:54 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Big switch to print the right error message
*/

static void	dump_err(char errcode)
{
	if (errcode == NOENVIRON)
		ft_putstr(NOENVIRON_STR);
	else if (errcode == NOWINDOW)
		ft_putstr(NOWINDOW_STR);
	else if (errcode == FAILSETENV)
		ft_putstr(FAILSETENV_STR);
	else if (errcode == FAILSETLOCAL)
		ft_putstr(FAILSETLOCAL_STR);
	else if (errcode == FAILSETSIGHDLR)
		ft_putstr(FAILSETSIGHDLR_STR);
	else if (errcode == FAILREAD)
		ft_putstr(FAILREAD_STR);
	else if (errcode == NODIR)
		ft_putstr(NODIR_STR);
	else if (errcode == NOMEM)
		ft_putstr(NOMEM_STR);
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
		ft_dlstdel(&env->line, &delvoid);
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
