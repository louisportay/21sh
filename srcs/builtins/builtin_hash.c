/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 19:27:34 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/19 21:02:15 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int			lhash_del(t_proc *p, t_ctx *ctx, int i)
{
	t_hentry		*e;
	t_list			*lsts[2];
	char			*str;
	int				ret;

	if (p->argv[i] == NULL)
	{
		p->data.out = list_create(ft_strdup(BU_H_EDREQU));
		return (1);
	}
	ret = 0;
	while (p->argv[i] != NULL)
	{
		if ((e = hash_lookup(ctx->hash, p->argv[i])) == NULL)
		{
			asprintf(&str, "221sh: hash: %s not found\n", p->argv[i]);
			lsts[1] = list_create(str);
			ft_list_insert(&p->data.out, lsts, lsts[1]);
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
	char			*str;
	t_hentry		*e;
	t_list			*lsts[2];

	if (p->argv[i] == NULL)
	{
		p->data.out = list_create(ft_strdup(BU_H_ETREQU));
		return (1);
	}
	ret = 0;
	while (p->argv[i] != NULL)
	{
		if ((e = hash_lookup(ctx->hash, p->argv[i])) == NULL)
			asprintf(&str, "221sh: hash: %s not found\n", p->argv[i]);
		else
			asprintf(&str, "1%s\n", (char *)e->content);
		lsts[1] = list_create(str);
		ft_list_insert(&p->data.out, lsts, lsts[1]);
		ret |= 1;
		i++;
	}
	return (ret);
}

static void			hashprint(char *key, void *value, void *data)
{
	char			*v;
	size_t			*l;
	char			*str;
	t_qbuf			*buf;

	v = (char *)value;
	l = (size_t *)((void **)data)[0];
	buf = (t_qbuf *)((void **)data)[1];
	asprintf(&str, "%-*s    %-*s\n", (int)l[0], key, (int)l[1], v);
	qbuf_add(buf, str);
	ft_strdel(&str);
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

static void			lsafe_list_last(t_proc *p, char *str)
{
	if (p->data.out != NULL)
		ft_list_last(p->data.out)->next = list_create(str);
	else
		p->data.out = list_create(str);
}

static int			lhash_print(t_proc *p, t_hdict *dict)
{
	size_t			len[2];
	t_qbuf			*buf;
	void			*arg;
	char			*str;

	if (dict->count == 0)
	{
		p->data.out = list_create(ft_strdup("121sh: hash empty\n"));
		return (0);
	}
	len[0] = 4;
	len[1] = 5;
	hash_foreach_data(dict, &largest, (void *)len);
	buf = qbuf_new(1 << 8);
	max(len, 4);
	max(len + 1, 5);
	asprintf(&str, "1%-*s    %-*s\n", (int)len[0], "bin:", (int)len[1],
				"path:");
	qbuf_add(buf, str);
	ft_strdel(&str);
	arg = (void *)((void *[]){(void *)len, (void *)buf});
	hash_foreach_data(dict, &hashprint, arg);
	str = qbuf_del(&buf);
	lsafe_list_last(p, str);
	return (0);
}

static int			lhash_find(t_proc *p, t_ctx *ctx, int i)
{
	char			*path;
	char			*str;
	int				ret;

	ret = 0;
	while (p->argv[i] != NULL)
	{
		if ((path = path_fromctx(p->argv[i], ctx)) == NULL)
		{
			asprintf(&str, "221sh: hash: %s not found\n", p->argv[i]);
			lsafe_list_last(p, str);
			hash_remove(ctx->hash, p->argv[i], &ft_memdel);
			ret |= 1;
		}
		else
		{
			path = ft_strdup(path);
			hash_add_or_mod(ctx->hash, ft_strdup(p->argv[i]), path, &ft_memdel);
		}
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
		lhash_print(p, ctx->hash);
	return (ret);
}
