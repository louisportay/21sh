/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashcreate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 19:18:35 by lportay           #+#    #+#             */
/*   Updated: 2017/12/08 09:02:53 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Mallocate a hash maillon with a 'key' and some 'data' inside of it
*/

t_hash	*hashcreate(char *key, void *data, size_t data_size)
{
	t_hash	*bucket;
	char	*tmp;

	if (!key || !(bucket = (t_hash *)malloc(sizeof(t_hash))) ||
	!(tmp = (char *)malloc(sizeof(char) * ft_strlen(key) + 1)))
		return (NULL);
	ft_strcpy(tmp, key);
	bucket->key = tmp;
	bucket->next = NULL;
	if (!data)
	{
		bucket->data = NULL;
		bucket->data_size = 0;
		return (bucket);
	}
	if (!(tmp = (char *)malloc(sizeof(char) * data_size)))
		return (NULL);
	ft_memcpy(tmp, data, data_size);
	bucket->data = tmp;
	bucket->data_size = data_size;
	return (bucket);
}
