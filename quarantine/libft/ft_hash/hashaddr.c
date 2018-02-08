/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashaddr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 19:18:35 by lportay           #+#    #+#             */
/*   Updated: 2017/12/02 11:01:28 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocate a hash maillon with a 'key' and some raw 'data' inside of it, the
** data is not copied.
*/

t_hash	*hashaddr(char *key, void *data, size_t data_size)
{
	t_hash	*bucket;
	char	*tmp;

	if (!key || !(bucket = (t_hash *)malloc(sizeof(t_hash))) ||
	!(tmp = (char *)malloc(sizeof(char) * ft_strlen(key) + 1)))
		return (NULL);
	ft_strcpy(tmp, key);
	bucket->key = tmp;
	bucket->next = NULL;
	bucket->data = data;
	bucket->data_size = data_size;
	if (!data)
		bucket->data_size = 0;
	return (bucket);
}
