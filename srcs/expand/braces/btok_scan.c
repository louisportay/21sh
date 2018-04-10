/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   braces_scan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 16:55:14 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/10 17:15:32 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_braces.h"

static int				l_skip_squote(char **str)
{
	char				*s;

	s = *str + 1;
	while (*s != '\0' && *s != '\'')
		s++;
	if (*s == '\0')
		return (1);
	*str = s + 1;
	return (0);
}

static int				l_skip_dquote(char **str)
{
	char				*s;

	s = *str + 1;
	while (*s != '\0' && *s != '\"')
	{
		if (*s == '\\')
			s++;
		s++;
	}
	if (*s == '\0')
		return (1);
	*str = s + 1;
	return (0);
}

static int				do_quotes(char **str)
{
	if (**str == '\'')
	{
		if (l_skip_squote(str))
			return (-1);
	}
	else if (**str == '\"')
	{
		if (l_skip_dquote(str))
			return (-1);
	}
	return (0);
}

int						braces_scan(char *str)
{
	while (*str != '\0')
	{
		if (*str == '{')
			return (1);
		else if (*str == '\\')
			str += 2;
		else if (*str == '\'' || *str == '\"')
		{
			if (do_quotes(&str) == -1)
				return (-1);
		}
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
