/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btok_lifecycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 17:09:15 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/13 15:23:55 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_braces.h"

t_btok					*btok_new(enum e_btoktype type, char *str)
{
	t_btok				*ret;

	if ((ret = (t_btok *)ft_memalloc(sizeof(t_btok))) == NULL)
		return (NULL);
	ret->type = type;
	ret->val = str;
	return (ret);
}

void					btok_free(t_btok **tok)
{
	ft_strdel(&((*tok)->val));
	ft_memdel((void **)tok);
}

void					btok_insert(t_btok **head, t_btok **curr, t_btok *tmp)
{
	if (*head == NULL)
		*head = tmp;
	else
		(*curr)->next = tmp;
	*curr = tmp;
}

void					btok_clear(t_btok **tokens)
{
	t_btok				*tok;
	t_btok				*tmp;

	tok = *tokens;
	*tokens = NULL;
	while (tok != NULL)
	{
		tmp = tok;
		tok = tok->next;
		btok_free(&tmp);
	}
}
