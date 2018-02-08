/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashindex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 16:10:52 by lportay           #+#    #+#             */
/*   Updated: 2017/11/13 17:01:57 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Return the index associated with a given key.
**
** The hashing algorithm is CLEARLY not optimized, doing something to fix that
** may be great.
*/

unsigned	hashindex(char *key)
{
	unsigned hashval;

	hashval = 0;
	while (*key)
		hashval = *key++ + hashval;
	return (hashval % HASHSIZE);
}

/*
** This is a little better but the keys are greater than HASHSIZE
*/

unsigned	hashindexFNV(char *key)
{
	unsigned hash;

	hash = OFFSET_BASIS_32;
	while (*key)
	{
		hash *= FNV_PRIME_32;
		hash ^= *key++;
	}
	return (hash);
}
