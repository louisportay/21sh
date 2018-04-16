/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_from_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 18:59:04 by lportay           #+#    #+#             */
/*   Updated: 2018/03/28 14:14:55 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	fill_token_str(char *s, t_token *tok, int toktype)
{
	t_dlist	*tmp;

	tmp = tok->first_letter;
	while (tmp != tok->last_letter)
	{
		*s++ = *(char *)tmp->data;
		tmp = tmp->next;
	}
	*s++ = *(char *)tmp->data;
	if (toktype == TLESS)
		*s++ = '\n';
	*s = '\0';
}

char	*allocate_token_str(t_token *tok, int toktype)
{
	t_dlist	*tmp;
	char	*s;
	size_t	len;

	len = 1;
	tmp = tok->first_letter;
	while (tmp != tok->last_letter)
	{
		len++;
		tmp = tmp->next;
	}
	if (toktype == TLESS)
		len++;
	if (!(s = ft_strnew(len + 1)))
		return (NULL);
	return (s);
}

char	*str_from_token(t_token *tok, int toktype)
{
	char	*s;

	if (!(s = allocate_token_str(tok, toktype)))
		return (NULL);
	fill_token_str(s, tok, toktype);
	return (s);
}
