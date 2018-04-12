/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching_match.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 15:48:36 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/13 17:35:25 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pattern_matching.h"

static int		l_match_string(char **str, t_mtok **token, t_mtok *next)
{
	char		*s1;
	char		*s2;
	size_t		len;
	int			ret;

	s1 = *str;
	s2 = (char *)next->data.str;
	len = ft_strlen(s2);
	while (*s1 != '\0' && (ret = ft_strncmp(s1, s2, len)) != 0)
		s1++;
	if (ret == 0)
	{
		*str = s1 + len;
		*token = next->next;
		return (0);
	}
	else
		return (1);
}

static int		l_match_anysi(char **str, t_mtok **token)
{
	if (*str != '\0')
	{
		*str = *str + 1;
		*token = (*token)->next;
		return (match_filename(str, token));
	}
	return (1);
}

int				match_filename(char **str, t_mtok **token)
{
	t_mtok		*next;

	if ((next = (*token)->next) == NULL)
	{
		*str = "";
		*token = NULL;
		return (0);
	}
	if (next->type == ANYSI)
		return (l_match_anysi(str, token));
	if (next->type == STRIN)
		return (l_match_string(str, token, next));
	if (next->type == FILEN)
	{
		*token = (*token)->next;
		return (match_filename(str, token));
	}
	else
	{
		*str = *str + 1;
		return (match_filename(str, token));
	}
	return (1);
}
