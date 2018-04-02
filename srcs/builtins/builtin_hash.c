/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 19:27:34 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/02 16:03:48 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int			lhash_del(t_proc *p, t_ctx *ctx, int i)
{
	t_hentry		*e;
	int				ret;

	if (p->argv[i] == NULL)
	{
		ft_putstr_fd(BU_H_EDREQU, STDERR_FILENO);
		return (1);
	}
	ret = 0;
	while (p->argv[i] != NULL)
	{
		if ((e = hash_lookup(ctx->hash, p->argv[i])) == NULL)
		{
			ft_dprintf(STDERR_FILENO, BU_H_ENOKEY, p->argv[i]);
			ret |= 1;
		}
		else
			hash_remove(ctx->hash, p->argv[i], &ft_memdel);
		i++;
	}
	return (ret);
}

static int			lhash_prt(t_proc *p, t_ctx *ctx, int i)
{
	int				ret;
	t_hentry		*e;

	if (p->argv[i] == NULL)
	{
		ft_putstr_fd(BU_H_ETREQU, STDERR_FILENO);
		return (1);
	}
	ret = 0;
	while (p->argv[i] != NULL)
	{
		if ((e = hash_lookup(ctx->hash, p->argv[i])) == NULL)
			ft_dprintf(STDERR_FILENO, BU_H_ENOKEY, p->argv[i]);
		else
			ft_printf("%s\n", (char *)e->content);
		ret |= 1;
		i++;
	}
	return (ret);
}

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

static int			lhash_print(t_hdict *dict)
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

static int			lhash_find(t_proc *p, t_ctx *ctx, int i)
{
	char			*path;
	int				ret;

	ret = 0;
	while (p->argv[i] != NULL)
	{
		if ((path = path_fromcache(p->argv[i], ctx)) == NULL)
		{
			ft_dprintf(STDERR_FILENO, BU_H_ENOKEY, p->argv[i]);
			hash_remove(ctx->hash, p->argv[i], &ft_memdel);
			ret |= 1;
		}
		else
			hash_add_or_mod(ctx->hash, ft_strdup(p->argv[i]), path, &ft_memdel);
		i++;
	}
	return (ret);
}

int					ft_hash(t_proc *p, t_ctx *ctx)
{
	int				f;
	int				ret;
	int				i;

	p->type = BUILTIN;
	ret = 0;
	i = 1;
	if ((f = bu_hash_getopts(p, ctx, &i)) == -1)
		return (1);
	else if (f == -2)
		return (0);
	if (f & BU_H_CLR)
		hash_empty(ctx->hash, &ft_memdel);
	if (f & BU_H_DEL)
		ret |= (lhash_del(p, ctx, i));
	else if (f & BU_H_PRT)
		ret |= (lhash_prt(p, ctx, i));
	if ((f & (BU_H_PRT | BU_H_DEL)) == 0 && p->argv[i] != NULL)
		ret |= lhash_find(p, ctx, i);
	if ((f == 0 && p->argv[i] == NULL) || (f & BU_H_LST) == BU_H_LST)
		lhash_print(ctx->hash);
	return (ret);
}
