/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashset_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 10:49:37 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/18 14:05:18 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashset.h"
#include "ft_string.h"

void				ft_hashset_free(t_hash_dict **dict,
									void (*ptr)(void **))
{
	if (dict == NULL || *dict == NULL)
		return ;
	ft_hashset_empty(*dict, ptr);
	ft_memdel((void **)&((*dict)->entries));
	ft_memdel((void **)dict);
}

void				ft_hashset_empty(t_hash_dict *dict, void (*ptr)(void **))
{
	size_t			i;
	t_hash_entry	*e;
	t_hash_entry	*tmp;

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
			ft_strdel(&tmp->key);
			ptr(&tmp->content);
			ft_memdel((void **)&tmp);
		}
		dict->entries[i] = NULL;
		i++;
	}
	dict->count = 0;
}
