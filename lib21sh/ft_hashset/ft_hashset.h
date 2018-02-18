/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hashset.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 10:47:35 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/18 17:30:39 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HASHSET_H
# define FT_HASHSET_H

# include <sys/types.h>
# include <stdlib.h>

# define HASH_SIZE 91
# define HASH_PRIME 17

typedef struct s_hash_entry	t_hash_entry;
typedef struct s_hash_dict	t_hash_dict;

struct						s_hash_entry
{
	char					*key;
	void					*content;
	t_hash_entry			*next;
};

struct						s_hash_dict
{
	size_t					size;
	int						prime;
	size_t					count;
	t_hash_entry			**entries;
};

t_hash_dict					*ft_hashset_create(size_t size, int prime);
t_hash_entry				*ft_hashset_add(t_hash_dict *dict, char *key,
											void *value);
t_hash_entry				*ft_hashset_lookup(t_hash_dict *dict, char *str);
u_int						ft_hashset_hash(t_hash_dict *dict, char *str);

void						ft_hashset_free(t_hash_dict **dict,
											void (*ptr_free)(void **));
void						ft_hashset_empty(t_hash_dict *dict,
												void (*ptr)(void **));
void						hash_remove(t_hash_dict *dict, char *key,
										void (*ptr)(void **));

void						hash_add_or_mod(t_hash_dict *dict, char *key,
											char *value, void (*ptr)(void **));

void						hash_foreach_data(t_hash_dict *dict,
												void (*func)(),
												void *data);

#endif
