/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 18:12:40 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/11 11:34:14 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

static int		scan_dquote(char **str, int *doll)
{
	char		*s;

	s = *str;
	while (*s != '\0' && *s != '\"')
	{
		if (*s == '\\')
			s++;
		else if (*s == '$')
			*doll = 1;
		s++;
	}
	if (*s == '\0')
		return (-1);
	s++;
	*str = s;
	return (*doll);
}

static int		squote(char **str)
{
	char		*s;

	s = *str;
	while (*s != '\0' && *s != '\'')
		s++;
	s++;
	if (*s == '\0')
		return (-1);
	*str = s;
	return (0);
}

int				scan_dollar(char *str)
{
	int			doll;

	doll = 0;
	if (str == NULL)
		return (0);
	while (*str != '\0')
	{
		if (*str == '\\')
			str += 2;
		else if (*str == '\'')
		{
			if (squote(&str) == -1)
				return (-1);
		}
		else if (*str == '\"')
		{
			if (scan_dquote(&str, &doll) == -1)
				return (-1);
		}
		else
		{
			doll |= *str == '$';
			str++;
		}
	}
	return (doll);
}
