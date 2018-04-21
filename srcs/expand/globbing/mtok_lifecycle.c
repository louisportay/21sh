/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtok_lifecycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 15:43:45 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/20 14:38:38 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

t_mtok				*mtok_create(enum e_mt_type type)
{
	t_mtok			*ret;

	if ((ret = (t_mtok *)ft_pmemalloc(sizeof(t_mtok), &on_emem, NOMEM)) == NULL)
		return (NULL);
	ret->type = type;
	ret->data.str = NULL;
	return (ret);
}

t_mtok				*mtok_create_mod(enum e_mt_type type, enum e_modtype mod)
{
	t_mtok			*ret;

	if ((ret = (t_mtok *)ft_pmemalloc(sizeof(t_mtok), &on_emem, NOMEM)) == NULL)
		return (NULL);
	ret->type = type;
	ret->data.mod = mod;
	return (ret);
}

t_mtok				*mtok_create_str(enum e_mt_type type, char *str)
{
	t_mtok		*ret;

	if ((ret = (t_mtok *)ft_pmemalloc(sizeof(t_mtok), &on_emem, NOMEM)) == NULL)
		return (NULL);
	ret->type = type;
	ret->data.str = str;
	return (ret);
}

void				mtok_free(t_mtok **mt)
{
	t_mtok			*m;

	if (mt == NULL || *mt == NULL)
		return ;
	m = *mt;
	if (m->type == STRIN || m->type == RANGE)
		ft_strdel(&m->data.str);
	ft_memdel((void **)mt);
}

void				mtok_clear(t_mtok **mt)
{
	t_mtok			*curr;
	t_mtok			*tmp;

	curr = *mt;
	*mt = NULL;
	while (curr != NULL)
	{
		tmp = curr;
		curr = curr->next;
		if (tmp->type == STRIN || tmp->type == RANGE)
			ft_strdel(&tmp->data.str);
		ft_memdel((void **)&tmp);
	}
}
