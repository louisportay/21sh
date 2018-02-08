/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashInsert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 16:32:03 by lportay           #+#    #+#             */
/*   Updated: 2017/08/23 17:48:18 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Insert the 'bucket' in the 'table', if bucket is already present and
** (overwrite == 1) the old 'data' is erased (with 'del') and the new one
** is replaced.
** == Return values ==
** 0 the 'bucket' is normally inserted
** 1 the old data has been replaced
** -1 Nothing has been done ('bucket' exists and overwrite != 1)
** ===================
*/

int	hashinsert(t_hash **table, t_hash *bucket, int overwrite,
void (*del)(void **))
{
	t_hash		*tmp;
	unsigned	hash;

	if ((tmp = hashlookup(table, bucket->key)) == NULL)
	{
		hash = hashindex(bucket->key);
		bucket->next = table[hash];
		table[hash] = bucket;
		return (0);
	}
	else if (overwrite != 0)
	{
		ft_strdel(&bucket->key);
		(*del)(&tmp->data);
		tmp->data_size = bucket->data_size;
		tmp->data = bucket->data;
		free(bucket);
		return (1);
	}
	return (-1);
}
