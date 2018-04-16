/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asmt.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:53:18 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/10 11:29:01 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

t_asmt					*asmt_fromtoken(t_token *tok)
{
	t_asmt				*asmt;
	t_dlist				*eq;

	asmt = (t_asmt *)ft_pmemalloc(sizeof(t_asmt), &on_emem, NOMEM);
	eq = dlst_findc(tok->first_letter, '=');
	asmt->key = dlst_pstr(tok->first_letter, eq);
	if (eq != tok->last_letter)
		asmt->value = dlst_pstr(eq->next, tok->last_letter->next);
	else
		asmt->value = ft_strnew(0);
	return (asmt);
}

void					asmt_update(t_asmt *asmt, t_asmt **new)
{
	t_asmt				*tnew;

	tnew = *new;
	*new = NULL;
	ft_strdel(&asmt->value);
	asmt->value = tnew->value;
	ft_strdel(&tnew->key);
	ft_memdel((void **)&tnew);
}

void					asmt_insert(t_asmt **head, t_asmt **curr, t_asmt *e)
{
	if (*head == NULL)
		*head = e;
	else
		(*curr)->next = e;
	*curr = e;
}

t_asmt					*asmt_find(t_asmt *asmt, char *key)
{
	while (asmt != NULL)
	{
		if (ft_strcmp(asmt->key, key) == 0)
			return (asmt);
		asmt = asmt->next;
	}
	return (NULL);
}
