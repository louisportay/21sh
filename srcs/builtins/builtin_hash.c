/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 19:27:34 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/15 19:58:23 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void		max(size_t *a, size_t b)
{
	if (*a < b)
		*a = b;
}

static void		hashprint(char *key, void *value, void *data)
{
	char		*v;
	size_t		*l;
	
	v = (char *)value;
	l = (size_t *)data;
	printf("%-*s    %-*s\n", (int)l[0], key, (int)l[1], v);
}

static void		largest(char *key, void *value, void *data)
{
	char		*v;
	size_t		*l;
	size_t		t[2];

	v = (char *)value;
	l = (size_t *)data;
	t[0] = ft_strlen(key);
	t[1] = ft_strlen(v);
	max(l, t[0]);
	max(l + 1, t[1]);
}

static int		print_hash(t_hash_dict *dict)
{
	size_t		len[2];

	hash_foreach_data(dict, &largest, (void *)len);
	max(len, 4);
	max(len + 1, 6);
	printf("key:    value:\n");
	hash_foreach_data(dict, &hashprint, len);
	return (0);
}

int				ft_hash(char **args, t_ctx *ctx)
{
	(void)args;
	return (print_hash(ctx->hash));
}
