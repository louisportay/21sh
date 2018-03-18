/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_from_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 18:59:04 by lportay           #+#    #+#             */
/*   Updated: 2018/03/17 19:01:48 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	fill_token_str(char *s, t_token *tok)
{
	t_dlist	*tmp;	

	tmp = tok->first_letter;
	while (tmp != tok->last_letter)
	{
		*s++ = *(char *)tmp->data;
		tmp = tmp->next;
	}
	*s++ = *(char *)tmp->data;
	*s = '\0';
}

char 	*allocate_token_str(t_token *tok)
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
	if (!(s = ft_strnew(len + 1)))
		return (NULL);
	return (s);
}

char	*str_from_token(t_token *tok)
{
	char	*s;

	if (!(s = allocate_token_str(tok)))
		return (NULL);
	fill_token_str(s, tok);
	return (s);
}
