/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtok_lifecycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 18:03:58 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/04 20:23:02 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

void			vtok_insert(t_vtok **head, t_vtok **curr, t_vtok *tmp)
{
	if (*head == NULL)
		*head = tmp;
	else
		(*curr)->next = tmp;
	*curr = tmp;
}

t_vtok			*vtok_new(enum e_vtype type, char c)
{
	t_vtok		*tok;

	if ((tok = (t_vtok *)ft_pmemalloc(sizeof(t_vtok), &on_emem, NOMEM)) == NULL)
		return (NULL);
	tok->data.c = c;
	tok->type = type;
	return (tok);
}

t_vtok			*vtok_newstr(enum e_vtype type, char *str)
{
	t_vtok		*tok;

	if ((tok = (t_vtok *)ft_pmemalloc(sizeof(t_vtok), &on_emem, NOMEM)) == NULL)
		return (NULL);
	tok->data.str = str;
	tok->type = type;
	return (tok);
}

void			vtok_del(t_vtok **tok)
{
	t_vtok		*t;

	if (tok == NULL || *tok == NULL)
		return ;
	t = *tok;
	*tok = NULL;
	if (t->type == VAWORD || t->type == VOTHER)
		ft_strdel(&t->data.str);
	ft_memdel((void **)&t);
}

void			vtok_clear(t_vtok **tok)
{
	t_vtok		*t;
	t_vtok		*tmp;

	t = *tok;
	*tok = NULL;
	while (t != NULL)
	{
		tmp = t;
		t = t->next;
		vtok_del(&tmp);
	}
}
