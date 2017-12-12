/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 10:48:13 by lportay           #+#    #+#             */
/*   Updated: 2017/12/11 12:21:55 by lportay          ###   ########.fr       */
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
