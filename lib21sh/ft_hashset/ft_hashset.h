/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashset.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 10:47:35 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/18 18:02:12 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HASHSET_H
# define FT_HASHSET_H

# include <sys/types.h>
# include <stdlib.h>

# define HASH_SIZE 91
# define HASH_PRIME 17

typedef struct s_hash_entry	t_hentry;
typedef struct s_hash_dict	t_hdict;

struct						s_hash_entry
{
	char					*key;
	void					*content;
	t_hentry				*next;
};

struct						s_hash_dict
{
	size_t					size;
	int						prime;
	size_t					count;
	t_hentry				**entries;
};

t_hdict						*hash_create(size_t size, int prime);
t_hentry					*hash_add(t_hdict *dict, char *key, void *value);
t_hentry					*hash_lookup(t_hdict *dict, char *str);
u_int						hash_hash(t_hdict *dict, char *str);

void						hash_free(t_hdict **dict,
										void (*ptr_free)(void **));
void						hash_empty(t_hdict *dict, void (*ptr)(void **));
void						hash_remove(t_hdict *dict, char *key,
										void (*ptr)(void **));

void						hash_add_or_mod(t_hdict *dict, char *key,
											char *value, void (*ptr)(void **));

void						hash_foreach_data(t_hdict *dict, void (*func)(),
												void *data);

#endif
