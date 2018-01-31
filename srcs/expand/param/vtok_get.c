/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtok_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 18:11:22 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/14 18:26:51 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

static t_vtok	*vtok_word(char **str)
{
	char		*s;
	char		*h;
	char		*ls;

	s = *str + 1;
	h = *str;
	while (ft_isalnum(*s) || *s == '_')
		s++;
	ls = ft_strndup(h, (size_t)(s - h));
	*str = s;
	return (vtok_newstr(VAWORD, ls));
}

static t_vtok	*vtok_other(char **str, int dq)
{
	char		*s;
	char		*ls;

	s = *str;
	while (*s != '\0' && ft_strindex(VACHR, *s) == -1)
	{
		if (*s == '\\')
			s += 2;
		else if (*s == '\'')
		{
			if (dq == 0)
			{
				s++;
				while (*s != '\'')
					s++;
			}
			s++;
		}
		else
			s++;
	}
	ls = ft_strndup(*str, (size_t)(s - *str));
	*str = s;
	return (vtok_newstr(VOTHER, ls));
}

static t_vtok	*vtok_next(char **str, int dq)
{
	t_vtok		*t;
	int			pos;

	if (**str == '\0')
		return (NULL);
	if ((pos = ft_strindex(VACHR, **str)) != -1)
	{
		t = vtok_new(pos, **str);
		*str = *str + 1;
		return (t);
	}
	else if (ft_isletter(**str))
		return (vtok_word(str));
	else
		return (vtok_other(str, dq));
}

t_vtok			*vtok_get(char *str)
{
	t_vtok		*tok[3];
	int			dq;

	tok[0] = NULL;
	tok[1] = NULL;
	tok[2] = NULL;
	dq = 0;
	while ((tok[2] = vtok_next(&str, dq)) != NULL)
	{
		vtok_insert(tok, tok + 1, tok[2]);
		if (tok[2]->type == VDQUOT)
			dq ^= 1;
	}
	return (tok[0]);
}
