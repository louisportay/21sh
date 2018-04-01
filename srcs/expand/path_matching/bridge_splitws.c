/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge_splitws.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 11:39:56 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/01 12:24:36 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_list.h"
#include "expand.h"

static void			l_skipsquote(char **str)
{
	char			*s;

	s = *str + 1;
	while (*s != '\'')
		s++;
	*str = s + 1;
}

static void			l_skipdquote(char **str)
{
	char			*s;

	s = *str + 1;
	while (*s != '\"')
	{
		if (*s == '\\')
			s += 2;
		else
			s++;
	}
	*str = s + 1;
}

static char			*get_next(char *str)
{
	while (*str != '\0')
	{
		if (*str == '\'')
			l_skipsquote(&str);
		else if (*str == '\"')
			l_skipdquote(&str);
		else if (*str == '\\')
			str += 2;
		else if (ft_strindex(WHITESPACES, *str) != -1)
			return (str);
		else
			str++;
	}
	return (str);
}

t_list				*bridge_strsplit(char *str)
{
	t_list			*lst[3];
	char			*n;
	char			*tmp;

	lst[0] = NULL;
	while (1)
	{
		while (ft_strindex(WHITESPACES, *str) != -1)
			str++;
		n = get_next(str);
		tmp = ft_strndup(str, (size_t)(n - str));
		lst[2] = list_create(tmp);
		ft_list_insert(lst, lst + 1, lst[2]);
		str = n;
		if (*n == '\0')
			break ;
	}
	return (lst[0]);
}
