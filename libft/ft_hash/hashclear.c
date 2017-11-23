/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashclear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 16:10:56 by lportay           #+#    #+#             */
/*   Updated: 2017/11/16 17:19:12 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Clear the whole hashtable, even stacked buckets
*/

void	hashclear(t_hash **table, void (*del)(void **))
{
	t_hash *tmp;
	int i;

	i = 0;
	while (i < HASHSIZE)
	{
		if (table[i])
		{
			tmp = table[i];
			while (tmp)
			{
				table[i] = table[i]->next;
				ft_strdel(&tmp->key);
				(*del)(&tmp->data);
				free(tmp);
				tmp = table[i];
			}
		}
		i++;
	}
}
