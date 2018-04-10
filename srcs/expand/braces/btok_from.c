/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btok_from.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 17:39:12 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/10 14:28:41 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_braces.h"

t_btok					*btok_from_squote(char **str, int *err)
{
	char				*s;
	char				*tmp;
	t_btok				*tok;

	s = *str + 1;
	*err = 0;
	while (*s != '\0' && *s != '\'')
		s++;
	if (*s == '\0')
	{
		*err = 1;
		return (NULL);
	}
	s++;
	tmp = ft_strndup(*str, s - *str);
	tok = btok_new(BOTHER, tmp);
	*str = s;
	return (tok);
}

t_btok					*btok_from_dquote(char **str, int *err)
{
	char				*s;
	char				*tmp;
	t_btok				*tok;

	s = *str + 1;
	*err = 0;
	while (*s != '\0' && *s != '\"')
	{
		if (*s == '\\')
		{
			if (*(s + 1) == '"')
				s += 2;
			else
				s++;
		}
		s++;
	}
	if (*s == '\0')
	{
		*err = 1;
		return (NULL);
	}
	s++;
	tmp = ft_strndup(*str, s - *str);
	tok = btok_new(BOTHER, tmp);
	*str = s;
	return (tok);
}

t_btok					*btok_from_other(char **str)
{
	char				*s;
	char				*tmp;
	t_btok				*tok;

	s = *str;
	while (*s != '\0' && ft_strindex("{},.$", *s) == -1)
	{
		if (*s == '\\')
			s++;
		s++;
	}
	tmp = ft_strndup(*str, s - *str);
	tok = btok_new(BOTHER, tmp);
	*str = s;
	return (tok);
}
