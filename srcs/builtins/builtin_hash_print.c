/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 20:10:31 by lportay           #+#    #+#             */
/*   Updated: 2018/04/09 20:11:53 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void			hashprint(char *key, void *value, void *data)
{
	char			*v;
	size_t			*l;

	v = (char *)value;
	l = (size_t *)data;
	ft_printf("%-*s    %-*s\n", (int)l[0], key, (int)l[1], v);
}

static void			largest(char *key, void *value, void *data)
{
	char			*v;
	size_t			*l;
	size_t			t[2];

	v = (char *)value;
	l = (size_t *)data;
	t[0] = ft_strlen(key);
	t[1] = ft_strlen(v);
	max(l, t[0]);
	max(l + 1, t[1]);
}

int			hash_print(t_hdict *dict)
{
	size_t			len[2];

	if (dict->count == 0)
	{
		ft_putstr("21sh: hash table empty\n");
		return (0);
	}
	len[0] = 4;
	len[1] = 5;
	hash_foreach_data(dict, &largest, (void *)len);
	max(len, 4);
	max(len + 1, 5);
	ft_printf("%-*s    %-*s\n", (int)len[0], "bin:", (int)len[1], "path:");
	hash_foreach_data(dict, &hashprint, len);
	return (0);
}
