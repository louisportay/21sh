/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashlookup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 16:29:53 by lportay           #+#    #+#             */
/*   Updated: 2017/11/16 16:43:33 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Search inside the whole table the bucket with the given 'key'
** Even the stacked buckets are inspected
** Pointer to the maillon if successful
** NULL if not
*/

t_hash	*hashlookup(t_hash **table, char *key)
{
	t_hash *tmp;

	tmp = table[hashindex(key)];
	while (tmp != NULL)
	{
		if (ft_strcmp(key, tmp->key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
