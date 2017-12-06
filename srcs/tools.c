/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 10:48:13 by lportay           #+#    #+#             */
/*   Updated: 2017/12/06 22:04:46 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** function written for tputs to output the characters
*/

int		ft_putchar_stdin(int c)
{
	write(STDIN_FILENO, &c, 1);
	return (c);
}

void	change_cursor_offset(t_21sh *env, int movement)
{
	env->cursor_offset[0] += movement;
	if (env->cursor_offset[0] >= env->ws.ws_col)
	{
		env->cursor_offset[0] -= env->ws.ws_col;
		env->cursor_offset[1]++;
	}
}

bool	isonlywhitespace(char *s)
{
	while (*s)
	{
		if (*s != '\t' && *s != ' ')
			return (false);
		s++;
	}
	return (true);
}
