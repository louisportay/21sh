/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 18:12:40 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/10 14:18:40 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

static int		scan_dquote(char **str)
{
	int			doll;

	doll = 0;
	while (**str != '\0' && **str != '\"')
	{
		if (**str == '\\')
			(*str) += 2;
		else if (**str == '$')
			doll = 1;
		else
			(*str)++;
	}
	if (**str == '\0')
		return (-1);
	(*str)++;
	return (doll);
}

int				scan_dollar(char *str)
{
	int			ret;
	int			doll;

	doll = 0;
	while (*str != '\0')
	{
		if (*str == '\\')
			str += 2;
		else if (*str == '\'')
		{
			while (*str != '\0' && *str != '\'')
				str++;
			str++;
			if (*str == '\0')
				return (-1);
		}
		else if (*str == '\"')
		{
			if ((ret = scan_dquote(&str)) != 0)
			{
				if (ret == -1)
					return (-1);
				else if (ret == 1)
					doll = 1;
			}
		}
		else if (*str == '$')
			doll = 1;
		else
			str++;
	}
	return (doll);
}
