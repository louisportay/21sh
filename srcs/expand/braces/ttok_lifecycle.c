/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttok_lifecycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 19:04:25 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/04 20:22:58 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_braces.h"

t_ttok					*ttok_newrng(enum e_ttoktype type, int l, int r)
{
	t_ttok				*tok;

	if ((tok = (t_ttok *)ft_pmemalloc(sizeof(t_ttok), &on_emem, NOMEM)) == NULL)
		return (NULL);
	tok->type = type;
	tok->data.rng[0] = l;
	tok->data.rng[1] = r;
	tok->data.rng[2] = l;
	return (tok);
}

t_ttok					*ttok_newmix(t_list *lst)
{
	t_ttok				*tok;

	if (lst == NULL)
		return (NULL);
	if ((tok = (t_ttok *)ft_pmemalloc(sizeof(t_ttok), &on_emem, NOMEM)) == NULL)
		return (NULL);
	tok->type = TMIXRNG;
	tok->data.elem[0] = lst;
	tok->data.elem[1] = lst;
	return (tok);
}

t_ttok					*ttok_newstr(char *str)
{
	t_ttok				*tok;

	if (str == NULL)
		return (NULL);
	if ((tok = (t_ttok *)ft_pmemalloc(sizeof(t_ttok), &on_emem, NOMEM)) == NULL)
		return (NULL);
	tok->type = TSTRING;
	tok->data.str = str;
	return (tok);
}

void					ttok_insert(t_ttok **head, t_ttok **curr, t_ttok *tmp)
{
	if (*head == NULL)
		*head = tmp;
	else
		(*curr)->next = tmp;
	*curr = tmp;
}

void					ttok_clear(t_ttok **tok)
{
	t_ttok				*tmp;
	t_ttok				*c;

	c = *tok;
	*tok = NULL;
	while (c != NULL)
	{
		tmp = c;
		c = c->next;
		if (tmp->type == TMIXRNG)
			ft_list_clear(tmp->data.elem, &ft_memdel);
		else if (tmp->type == TSTRING)
			ft_strdel(&tmp->data.str);
		ft_memdel((void **)&tmp);
	}
}
