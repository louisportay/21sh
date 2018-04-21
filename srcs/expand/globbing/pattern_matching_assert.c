/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching_assert.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 13:35:27 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/07 15:05:35 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pattern_matching.h"

static int		compare_filen_strin(char *str, size_t pos, t_mtok *token)
{
	char		*s;
	size_t		len;

	s = token->next->data.str;
	len = ft_strlen(s);
	while (str[pos] != '\0' && ft_strncmp(str + pos, s, len) != 0)
		pos++;
	if (str[pos] == '\0')
		return (1);
	if (compare(str, pos + len, token->next->next) == 0)
		return (0);
	return (compare(str, pos + 1, token));
}

static int		compare_filen(char *str, size_t pos, t_mtok *token)
{
	if (token->next == NULL)
		return (0);
	else if (token->next->type == STRIN)
		return (compare_filen_strin(str, pos, token));
	else if (token->next->type == ANYSI)
	{
		if (str[pos] == '\0')
			return (1);
		if (compare(str, pos + 1, token->next->next) == 0)
			return (0);
		return (compare(str, pos + 1, token));
	}
	else if (token->next->type == FILEN)
		return (compare(str, pos, token->next));
	return (1);
}

int				compare(char *str, size_t pos, t_mtok *token)
{
	char		*s;
	size_t		len;

	if (token == NULL)
		return (str[pos] != '\0');
	if (token->type == ANYSI)
		return (str[pos] == '\0' ? 1 : compare(str, pos + 1, token->next));
	if (token->type == STRIN)
	{
		s = token->data.str;
		len = ft_strlen(s);
		if (ft_strncmp(str + pos, s, len) != 0)
			return (1);
		return (compare(str, pos + len, token->next));
	}
	if (token->type == RANGE)
	{
		if (ft_strindex(token->data.str, str[pos]) == -1)
			return (1);
		return (compare(str, pos + 1, token->next));
	}
	if (token->type == FILEN)
		return (compare_filen(str, pos, token));
	return (1);
}

int				match(char *str, t_mtok *tokens)
{
	return (compare(str, 0, tokens) == 0);
}
