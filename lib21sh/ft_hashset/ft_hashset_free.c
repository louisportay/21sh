/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashset_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 10:49:37 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/06 15:58:21 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashset.h"

void				ft_hashset_free(t_hash_dict **dict,
									void (*ptr_free)(void **))
{
	size_t			i;
	t_hash_entry	*e;
	t_hash_entry	*tmp;

	if (dict == NULL || *dict == NULL)
		return ;
	i = 0;
	while (i < (*dict)->size)
	{
		e = (*dict)->entries[i];
		while (e != NULL)
		{
			tmp = e;
			e = e->next;
			if (ptr_free != NULL)
				ptr_free((void **)(&tmp));
		}
		e = NULL;
		i++;
	}
	ft_memdel((void **)&((*dict)->entries));
	ft_memdel((void **)dict);
}
