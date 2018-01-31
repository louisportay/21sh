/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btok_from.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 17:39:12 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/10 19:35:57 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_braces.h"

t_btok					*btok_from_squote(char **str)
{
	char				*s;
	char				*tmp;
	t_btok				*tok;

	s = *str + 1;
	while (*s != '\'')
		s++;
	s++;
	tmp = ft_strndup(*str, s - *str);
	tok = btok_new(BOTHER, tmp);
	*str = s;
	return (tok);
}

t_btok					*btok_from_dquote(char **str)
{
	char				*s;
	char				*tmp;
	t_btok				*tok;

	s = *str + 1;
	while (*s != '\"')
	{
		if (*s == '\\')
			s++;
		s++;
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
