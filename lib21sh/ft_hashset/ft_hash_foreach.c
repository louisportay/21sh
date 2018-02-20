/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_foreach.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 19:58:37 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/18 18:05:44 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashset.h"

void				hash_foreach_data(t_hdict *dict, void (*func)(),
										void *data)
{
	t_hentry		*e;
	t_hentry		**d;
	size_t			i;
	size_t			l;

	i = 0;
	l = dict->size;
	d = dict->entries;
	while (i < l)
	{
		e = d[i];
		while (e != NULL)
		{
			func(e->key, e->content, data);
			e = e->next;
		}
		i++;
	}
}
