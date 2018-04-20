/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtok_match.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 15:02:22 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/20 15:02:50 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

static int		lmatch_rng(char *str, t_mtok *tok)
{
	if (str == NULL || *str == '\0')
		return (0);
	if (ft_strindex(tok->data.str, *str) == -1)
		return (0);
	return (mtok_match(str + 1, tok->next));
}

static int		lmatch_str(char *str, t_mtok *tok)
{
	char		*s;
	size_t		len;

	if (str == NULL || *str == '\0')
		return (0);
	s = tok->data.str;
	len = ft_strlen(s);
	if (ft_strncmp(str, s, len) == 0)
		return (mtok_match(str + len, tok->next));
	return (0);
}

static int		lmatch_any(char *str, t_mtok *tok)
{
	if (str == NULL || *str == '\0')
		return (0);
	return (mtok_match(str + 1, tok->next));
}

static int		lmatch_fil(char *str, t_mtok *tok)
{
	if (tok->next == NULL)
		return (1);
	while (*str != '\0')
	{
		if (mtok_match(str, tok->next) == 1)
			return (1);
		str++;
	}
	return (0);
}

int				mtok_match(char *str, t_mtok *tok)
{
	if (str == NULL || (*str == '\0' && tok != NULL && tok->type != FILEN))
		return (0);
	if (tok == NULL)
		return (*str == '\0');
	if (tok->type == ANYSI)
		return (lmatch_any(str, tok));
	else if (tok->type == STRIN)
		return (lmatch_str(str, tok));
	else if (tok->type == RANGE)
		return (lmatch_rng(str, tok));
	else if (tok->type == FILEN)
		return (lmatch_fil(str, tok));
	return (0);
}
