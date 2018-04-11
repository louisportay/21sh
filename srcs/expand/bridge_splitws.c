/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge_splitws.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 11:39:56 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/11 12:00:24 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_list.h"
#include "expand.h"

static int			l_skipsquote(char **str)
{
	char			*s;

	s = *str + 1;
	while (*s != '\0' && *s != '\'')
		s++;
	if (*s == '\0')
		return (-1);
	*str = s + 1;
	return (0);
}

static int			l_skipdquote(char **str)
{
	char			*s;

	s = *str + 1;
	while (*s != '\0' && *s != '\"')
	{
		if (*s == '\\')
			s += 2;
		else
			s++;
	}
	if (*s == '\0')
		return (-1);
	*str = s + 1;
	return (0);
}

static char			*get_next(char *str)
{
	while (*str != '\0')
	{
		if (*str == '\'')
		{
			if (l_skipsquote(&str) == -1)
				return (NULL);
		}
		else if (*str == '\"')
		{
			if (l_skipdquote(&str) == -1)
				return (NULL);
		}
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

	if (str == NULL)
		return (NULL);
	lst[0] = NULL;
	while (1)
	{
		while (*str != '\0' && ft_strindex(WHITESPACES, *str) != -1)
			str++;
		if ((n = get_next(str)) == NULL)
			return (NULL);
		if ((tmp = ft_strndup(str, (size_t)(n - str))) == NULL)
			fatal_err(NOMEM, get_ctxaddr());
		lst[2] = list_create(tmp);
		ft_list_insert(lst, lst + 1, lst[2]);
		str = n;
		if (*n == '\0')
			break ;
	}
	return (lst[0]);
}
