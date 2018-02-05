/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 19:10:15 by lportay           #+#    #+#             */
/*   Updated: 2018/02/05 22:54:08 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Function which print the right error message
*/

void	dump_err(char errcode)
{
	t_keyval err[7];
	int 	i;

	err[0] = KEY_VAL(NOENVIRON, NOENVIRON_STR);
	err[1] = KEY_VAL(NOMEM, NOMEM_STR);
	err[2] = KEY_VAL(NODIR, NODIR_STR);
	err[3] = KEY_VAL(FAILSETSIGHDLR, FAILSETSIGHDLR_STR);
	err[4] = KEY_VAL(FAILREAD, FAILREAD_STR);
	err[5] = KEY_VAL(BADQUOTES, BADQUOTES_STR);
	err[6] = KEY_VAL(0, NULL);
	i = 0;
	while (errcode != err[i].key && err[i].key)
		i++;
	if (err[i].key)
		ft_putstr_fd(STDERR_FILENO, err[i].val);
}

/*
** Print the error message and exit
*/

void		fatal_err(char errcode, t_21sh *env)
{
	dump_err(errcode);
	wrap_exit(EXIT_FAILURE, env);
}

/*
** Free everything
*/

void	wrap_exit(int status, t_21sh *env)
{
	if (env->line.line)
	//ft_dlsthead(&env->line);//
		ft_dlstdel(&env->line.line, &delvoid);
	if (env->line.yank)
	//ft_dlsthead(&env->yank);//
		ft_dlstdel(&env->line.yank, &delvoid);

//	if (env->line.linestate)
//		stack_del(&env->line.linestate);

	if (env->hist.list)//faire une fonction dédiée
	{
	////ft_dlsthead(&env->histlist);//
		if (env->hist.list->next)
		{
			trim_history(&env->hist.list->next, get_kvp("HISTFILESIZE", env->local));
			save_history(env->local, env->hist.list->next);
			env->hist.list = env->hist.list->next;
			ft_dlstdelone(&env->hist.list->previous, &delvoid);
			ft_dlstdel(&env->hist.list, &del_histentry);
		}
		else
			ft_dlstdelone(&env->hist.list, &delvoid);
	}
	if (env->environ)
		delete_kvp(&env->environ);
	if (env->local)
		delete_kvp(&env->local);
	write(STDOUT_FILENO, "exit\n", 6);
	if (env->line_edition == true)
		tcsetattr(STDIN_FILENO, TCSADRAIN, &env->oldtios);	
	exit(status);
}
