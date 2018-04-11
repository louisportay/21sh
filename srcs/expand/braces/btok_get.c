/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btok_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 16:53:28 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/11 10:42:34 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_braces.h"

t_btok					*btok_next(char **str, int *err)
{
	char				*s;
	char				buf[2];
	int					pos;

	buf[1] = '\0';
	*err = 0;
	if (**str == '\0')
		return (NULL);
	if ((pos = ft_strindex("{},.$", **str)) != -1)
	{
		buf[0] = **str;
		s = ft_strdup(buf);
		(*str)++;
		return (btok_new(pos, s));
	}
	else if (**str == '\'')
		return (btok_from_squote(str, err));
	else if (**str == '\"')
		return (btok_from_dquote(str, err));
	else
		return (btok_from_other(str));
}

t_btok					*btok_get(char *str, int *err)
{
	t_btok				*tok[3];

	tok[0] = NULL;
	*err = 0;
	while ((tok[2] = btok_next(&str, err)) != NULL)
		btok_insert(tok, tok + 1, tok[2]);
	if (*err)
	{
		btok_clear(tok);
		return (NULL);
	}
	return (tok[0]);
}
