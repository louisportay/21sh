/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 16:01:58 by lportay           #+#    #+#             */
/*   Updated: 2017/11/16 15:01:26 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HASH_H
# define FT_HASH_H

# define HASHSIZE 32
# define OFFSET_BASIS_32 2166136261
# define FNV_PRIME_32 16777619

typedef struct		s_hash
{
	char			*key;
	void			*data;
	size_t			data_size;
	struct s_hash	*next;
}					t_hash;

unsigned	hashindex(char *key);
unsigned	hashindexFNV(char *key);
void		hashinit(t_hash **table);
int			hashinsert(t_hash **table, t_hash *bucket, int overwrite,
			void (*del)(void **));
int			hashdel(t_hash **table, char *key, void (*del)(void **));
void		hashclear(t_hash **table, void (*del)(void **));
t_hash		*hashlookup(t_hash **table, char *key);
t_hash		*hashcreate(char *key, void *data, size_t data_size);

#endif
