/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 18:16:05 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/05 18:30:50 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*token_to_str(t_token *tok)
{
	char 	*head;
	char	*s;
	t_dlist	*tmp;
	size_t	len;

	len = 1;
	tmp = tok->first_letter;
	while (tmp != tok->last_letter)
	{
		len++;
		tmp = tmp->next;
	}
	if (!(s = ft_strnew(len + 1)))
		return (NULL);
	head = s;
	while (tok->first_letter != tok->last_letter)
	{
		*s++ = *(char *)tok->first_letter->content;
		tok->first_letter = tok->first_letter->next;
	}
	*s++ = *(char *)tmp->content;
	*s = '\0';
	return (head);
}

/*
**	FT_STRINDEX HAS TO BE REMOVED
*/

static int				ft_strindex(const char *str, const char c)
{
	int					i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void					update_env(char ***env, t_token *tokens)
{
	char				*pair;
	int					pos;
	int					astrpos;

	while (tokens != NULL)
	{
		pair = token_to_str(tokens);
		pos = ft_strindex(pair, '=');
		if ((astrpos = ft_astr_nbeginswith(*env, pair, pos)) != -1)
		{
			ft_strdel((*env) + astrpos);
			(*env)[astrpos] = pair;
		}
		else
			ft_astr_append(env, pair);
	}
}
