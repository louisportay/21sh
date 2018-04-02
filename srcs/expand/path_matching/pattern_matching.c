/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 15:47:26 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/02 19:06:33 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pattern_matching.h"

int				get_string(char **matcher, t_mtok **tmp)
{
	t_qbuf		*buf;
	char		*str;

	buf = qbuf_new(1 << 8);
	while (**matcher != '\0' && ft_strindex(SPEC_CHR, **matcher) == -1)
	{
		if (**matcher == '\\')
			(*matcher)++;
		qbuf_addc(buf, **matcher);
		(*matcher)++;
	}
	if ((str = qbuf_del(&buf)) == NULL)
		return (-1);
	if ((*tmp = mtok_create_str(STRIN, str)) == NULL)
	{
		ft_strdel(&str);
		return (-1);
	}
	return (1);
}

static int		l_get_nret(char **matcher, t_mtok **tok)
{
	int			pos;

	if ((pos = ft_strindex(SPEC_CHR, **matcher)) != -1)
		return (get_matcher(pos)(matcher, tok));
	else
		return (get_string(matcher, tok));
}

static int		normal_matcher(char *matcher, t_mtok **tokens)
{
	t_mtok		*tok[3];
	int			ret;
	char		*orig;

	tok[0] = NULL;
	tok[1] = NULL;
	tok[2] = NULL;
	orig = matcher;
	while (*matcher != '\0')
	{
		ret = l_get_nret(&matcher, tok + 2);
		if (ret == 0)
		{
			*tokens = mtok_create_str(STRIN, ft_strdup(orig));
			return (*tokens != NULL ? 1 : -1);
		}
		else if (ret == -1)
			break ;
		if (tok[2] != NULL)
			mtok_insert(tok, tok + 1, tok[2]);
		else
			break ;
		tok[2] = NULL;
	}
	*tokens = tok[0];
	return (1);
}

int				get_matcher_tokens(char *matcher, t_mtok **tokens, int flags)
{
	if (flags == EXTOP)
		return (extended_matcher(matcher, tokens));
	return (normal_matcher(matcher, tokens));
}
