/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 10:48:54 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/18 17:31:24 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashset.h"
#include "ft_string.h"

u_int				ft_hashset_hash(t_hash_dict *dict, char *str)
{
	u_int			hashval;

	if (dict == NULL || str == NULL)
		return ((u_int)-1);
	hashval = 0;
	while (*str != '\0')
	{
		hashval = *str + dict->prime * hashval;
		str++;
	}
	return (hashval % dict->size);
}

t_hash_entry		*ft_hashset_lookup(t_hash_dict *dict, char *str)
{
	t_hash_entry	*entry;

	if (dict == NULL || str == NULL || dict->count == 0)
		return (NULL);
	entry = dict->entries[ft_hashset_hash(dict, str)];
	while (entry != NULL && ft_strcmp(str, entry->key) != 0)
		entry = entry->next;
	return (entry);
}

t_hash_entry		*ft_hashset_add(t_hash_dict *dict, char *key, void *value)
{
	t_hash_entry	*entry;
	u_int			val;

	if (dict == NULL || key == NULL)
		return (NULL);
	if (ft_hashset_lookup(dict, key) != NULL)
		return (NULL);
	if ((entry = (t_hash_entry *)ft_memalloc(sizeof(t_hash_entry))) == NULL)
		return (NULL);
	entry->key = key;
	entry->content = value;
	val = ft_hashset_hash(dict, key);
	entry->next = dict->entries[val];
	dict->count++;
	return (dict->entries[val] = entry);
}

t_hash_dict			*ft_hashset_create(size_t size, int prime)
{
	t_hash_dict		*dict;

	if ((dict = (t_hash_dict *)ft_memalloc(sizeof(t_hash_dict))) == NULL)
		return (NULL);
	dict->size = size;
	dict->prime = prime;
	dict->entries = (t_hash_entry **)ft_memalloc(sizeof(t_hash_entry *) * size);
	if (dict->entries == NULL)
	{
		free(dict);
		return (NULL);
	}
	return (dict);
}

void				hash_add_or_mod(t_hash_dict *dict, char *key, char *value,
									void (*ptr)(void **))
{
	t_hash_entry	*e;

	if ((e = ft_hashset_lookup(dict, key)) != NULL)
	{
		ptr(e->content);
		e->content = value;
		return ;
	}
	ft_hashset_add(dict, key, value);
}
