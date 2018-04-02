/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashset_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 10:49:37 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/02 13:56:57 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashset.h"
#include "ft_string.h"

void			hash_free(t_hdict **dict,
									void (*ptr)(void **))
{
	if (dict == NULL || *dict == NULL)
		return ;
	hash_empty(*dict, ptr);
	ft_memdel((void **)&((*dict)->entries));
	ft_memdel((void **)dict);
}

void			del_entry(t_hentry **e, void (*ptr)(void **))
{
	ft_strdel(&(*e)->key);
	if (ptr != NULL)
		ptr(&(*e)->content);
	ft_memdel((void **)e);
}

void			hash_empty(t_hdict *dict, void (*ptr)(void **))
{
	size_t		i;
	t_hentry	*e;
	t_hentry	*tmp;

	if (dict == NULL)
		return ;
	i = 0;
	while (i < dict->size)
	{
		e = dict->entries[i];
		while (e != NULL)
		{
			tmp = e;
			e = e->next;
			del_entry(&tmp, ptr);
		}
		dict->entries[i] = NULL;
		i++;
	}
	dict->count = 0;
}

void			hash_remove(t_hdict *dict, char *key,
								void (*ptr)(void **))
{
	u_int		i;
	t_hentry	*e;
	t_hentry	*tmp;
	t_hentry	*prev;

	i = hash_hash(dict, key);
	prev = NULL;
	e = dict->entries[i];
	while (e != NULL)
	{
		tmp = e;
		e = e->next;
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (prev == NULL)
				dict->entries[i] = e;
			else
				prev->next = e;
			del_entry(&tmp, ptr);
			dict->count--;
			return ;
		}
		prev = tmp;
	}
}
