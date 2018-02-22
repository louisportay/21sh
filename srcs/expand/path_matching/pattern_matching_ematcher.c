/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching_ematcher.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 16:30:24 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/22 13:22:31 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_matching.h"

static int		get_extstring(char **matcher, t_mtok **tmp)
{
	t_qbuf		*buf;
	char		*str;

	buf = qbuf_new(1 << 8);
	while (**matcher != '\0' && ft_strindex(SPEC_CHR_OP, **matcher) == -1
			&& **matcher != ')')
	{
		if (ft_strindex("+@!", **matcher) != -1 && (*matcher)[1] == '(')
			break ;
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

static int		exp_pat(char **matcher, t_mtok **tokens)
{
	if (ft_strncmp(*matcher, "?(", 2) == 0)
		*tokens = mtok_create_mod(RNMOD, MP_01);
	else if (ft_strncmp(*matcher, "*(", 2) == 0)
		*tokens = mtok_create_mod(RNMOD, MP_0N);
	else if (ft_strncmp(*matcher, "+(", 2) == 0)
		*tokens = mtok_create_mod(RNMOD, MP_1N);
	else if (ft_strncmp(*matcher, "@(", 2) == 0)
		*tokens = mtok_create_mod(RNMOD, MP_1S);
	else if (ft_strncmp(*matcher, "!(", 2) == 0)
		*tokens = mtok_create_mod(RNMOD, MP_EX);
	else
		return (0);
	*matcher += 2;
	return (1);
}

static int		l_get_ret(char **matcher, t_mtok **tok)
{
	int			pos;

	if (exp_pat(matcher, tok) != 0)
		return (1);
	else if (**matcher == ')')
	{
		*tok = mtok_create(MP_CL);
		(*matcher)++;
		return (1);
	}
	else if (**matcher == '|')
	{
		*tok = mtok_create(MP_PI);
		(*matcher)++;
		return (1);
	}
	else if ((pos = ft_strindex(SPEC_CHR_OP, **matcher)) != -1)
		return (get_matcher(pos)(matcher, tok));
	else
		return (get_extstring(matcher, tok));
}

int				extended_matcher(char *matcher, t_mtok **tokens)
{
	t_mtok		*tok[3];
	int			ret;
	char		*orig;

	tok[0] = NULL;
	tok[2] = NULL;
	orig = matcher;
	while (*matcher != '\0')
	{
		if ((ret = l_get_ret(&matcher, tok + 2)) == 0)
		{
			*tokens = mtok_create_str(STRIN, ft_strdup(orig));
			return (1);
		}
		else if (ret == -1)
			break ;
		if (tok[2] != NULL)
			mtok_insert(tok, tok + 1, tok[2]);
		else
			break ;
	}
	*tokens = tok[0];
	return (1);
}
