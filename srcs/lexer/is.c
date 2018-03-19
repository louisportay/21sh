/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 20:58:07 by lportay           #+#    #+#             */
/*   Updated: 2018/03/18 21:00:07 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** '`' 42SH
** c == '`' ||
*/

int		is_quoting(char c)
{
	if (c == '\\' ||
		c == '\'' ||
		c == '"' ||
		c == '#' ||
		c == '(' ||
		c == ')' ||
		c == '{' ||
		c == '}')
		return (1);
	return (0);
}

int	is_metachar(char c)
{
	if (c == '|' || c == '&' || c == ';' || c == '<' || c == '>' || ft_isblank(c))
		return (1);
	return (0);
}

int		is_max_operator(int n)
{
		if (n & (OR_IF | AND_IF |
			DGREAT | LESSAND | GREATAND | ANDDGREAT | TLESS |
			NEWLINE | SEMICOL))
			return (1);
		return (0);
}

int		is_extendable_operator(int n)
{
		if (n & (OR | AND | LESS | GREAT | DLESS | ANDGREAT))
			return (1);
		return (0);
}
