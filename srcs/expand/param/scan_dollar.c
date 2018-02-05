/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 18:12:40 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/08 18:12:44 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

static int		scan_dquote(char **str)
{
	while (**str != '\"')
	{
		if (**str == '\\')
			(*str) += 2;
		else if (**str == '$')
			return (1);
		else
			(*str)++;
	}
	(*str)++;
	return (0);
}

int				scan_dollar(char *str)
{
	while (*str != '\0')
	{
		if (*str == '\\')
			str += 2;
		else if (*str == '\'')
		{
			while (*str != '\'')
				str++;
			str++;
		}
		else if (*str == '\"')
		{
			if (scan_dquote(&str) == 1)
				return (1);
		}
		else if (*str == '$')
			return (1);
		else
			str++;
	}
	return (0);
}
