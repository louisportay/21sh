/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   braces_scan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 16:55:14 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/10 17:07:49 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_braces.h"

static void				l_skip_squote(char **str)
{
	char				*s;

	s = *str + 1;
	while (*s != '\'')
		s++;
	*str = s + 1;
}

static void				l_skip_dquote(char **str)
{
	char				*s;

	s = *str + 1;
	while (*s != '\"')
	{
		if (*s == '\\')
			s++;
		s++;
	}
	*str = s + 1;
}

int						braces_scan(char *str)
{
	while (*str != '\0')
	{
		if (*str == '{')
			return (1);
		else if (*str == '\\')
			str += 2;
		else if (*str == '\'')
			l_skip_squote(&str);
		else if (*str == '\"')
			l_skip_dquote(&str);
		else if (*str == '$')
		{
			if (str[1] == '{')
				str += 2;
			else
				str++;
		}
		else
			str++;
	}
	return (0);
}
