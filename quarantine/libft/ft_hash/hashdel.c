/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashdel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 16:36:42 by lportay           #+#    #+#             */
/*   Updated: 2017/11/16 16:43:25 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Delete (if exists) the bucket with the given 'key' in the 'table' with 'del'
** The stacked buckets are searched and the links are preserved.
*/

int	hashdel(t_hash **table, char *key, void (*del)(void **))
{
	t_hash *tmp;
	t_hash *prev;

	tmp = table[hashindex(key)];
	if (ft_strcmp(key, tmp->key) == 0)
		table[hashindex(key)] = tmp->next;
	prev = tmp;
	while (tmp != NULL)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			prev->next = tmp->next;
			ft_strdel(&tmp->key);
			(*del)(&tmp->data);
			free(tmp);
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (-1);
}
