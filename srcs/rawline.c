/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rawline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 10:26:30 by lportay           #+#    #+#             */
/*   Updated: 2017/12/12 17:50:58 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Called when:
** 				-line editing mode not available (missing termcap, whatever...)
**				-When the STDIN_FILENO is not a Terminal
**				-When a shell script is given in input (sweet dream...)
*/

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
	ft_dlstprint(env->line->next, "");
//	print_line(env, env->line->next);//
	write(1, "\n", 1);//
	/////////
	
	ft_dlstdel(&env->line, &delvoid);//
}
