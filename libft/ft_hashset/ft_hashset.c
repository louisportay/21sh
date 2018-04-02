/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 10:48:54 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/02 16:05:53 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hashset.h"
#include "ft_string.h"

u_int			hash_hash(t_hdict *dict, char *str)
{
	u_int		hashval;

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

t_hentry		*hash_lookup(t_hdict *dict, char *str)
{
	t_hentry	*entry;

	if (dict == NULL || str == NULL || dict->count == 0)
		return (NULL);
	entry = dict->entries[hash_hash(dict, str)];
	while (entry != NULL && ft_strcmp(str, entry->key) != 0)
		entry = entry->next;
	return (entry);
}

t_hentry		*hash_add(t_hdict *dict, char *key, void *value)
{
	t_hentry	*entry;
	u_int		val;

	if (dict == NULL || key == NULL)
		return (NULL);
	if (hash_lookup(dict, key) != NULL)
		return (NULL);
	if ((entry = (t_hentry *)ft_memalloc(sizeof(t_hentry))) == NULL)
		return (NULL);
	entry->key = key;
	entry->content = value;
	val = hash_hash(dict, key);
	entry->next = dict->entries[val];
	dict->count++;
	return (dict->entries[val] = entry);
}

t_hdict			*hash_create(size_t size, int prime)
{
	t_hdict		*dict;

	if ((dict = (t_hdict *)ft_memalloc(sizeof(t_hdict))) == NULL)
		return (NULL);
	dict->size = size;
	dict->prime = prime;
	dict->entries = (t_hentry **)ft_memalloc(sizeof(t_hentry *) * size);
	if (dict->entries == NULL)
	{
		free(dict);
		return (NULL);
	}
	return (dict);
}

void			hash_add_or_mod(t_hdict *dict, char *key, char *value,
									void (*ptr)(void **))
{
	t_hentry	*e;

	if ((e = hash_lookup(dict, key)) != NULL)
	{
		ptr(&e->content);
		e->content = value;
		ft_strdel(&key);
		return ;
	}
	hash_add(dict, key, value);
}
