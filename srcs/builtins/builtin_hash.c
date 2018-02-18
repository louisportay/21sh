/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 19:27:34 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/18 18:19:09 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

#define BU_H_EEMPTY ("121sh: hash empty\n")
#define BU_H_CLR (1 << 0)
#define BH_H_INH (1 << 1)
#define BU_H_DEL (1 << 2)
#define BU_H_PRT (1 << 3)
#define BU_H_LST (1 << 4)

#define BU_H_ETREQU ("221sh: hash: -t: option requires an argument\n")
#define BU_H_EDREQU ("221sh: hash: -d: option requires an argument\n")
#define BU_H_EPREQU ("221sh: hash: -p: option requires two arguments\n")
#define BU_H_USAGE_ ("21sh: usage: hash [-lr] [-p pathname] [-dt] [name ...]\n")

static int			lhash_inh(t_proc *p, t_ctx *ctx, int i, int j)
{
	char			*key;
	char			*value;
	int				k;

	if (p->argv[i][j + 1] != '\0')
	{
		if (p->argv[i + 1] == NULL)
		{
			p->data.out = list_create(ft_strdup(BU_H_EPREQU));
			return (-1);
		}
		k = i + 1;
		key = ft_strdup(p->argv[i] + j + 1);
	}
	else
	{
		if (p->argv[i + 1] == NULL || p->argv[i + 2] == NULL)
		{
			p->data.out = list_create(ft_strdup(BU_H_EPREQU));
			return (-1);
		}
		key = ft_strdup(p->argv[i + 1]);
		k = i + 2;
	}
	while (p->argv[k + 1] != NULL)
		k++;
	value = ft_strdup(p->argv[k]);
	hash_add_or_mod(ctx->hash, key, value, &ft_memdel);
	return (0);
}

static int			lhash_del(t_proc *p, t_ctx *ctx, int i)
{
	t_hentry	*e;
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
	t_hentry	*e;
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



static void		max(size_t *a, size_t b)
{
	if (*a < b)
		*a = b;
}

static void		hashprint(char *key, void *value, void *data)
{
	char		*v;
	size_t		*l;
	char		*str;
	t_qbuf		*buf;
	
	v = (char *)value;
	l = (size_t *)((void **)data)[0];
	buf = (t_qbuf *)((void **)data)[1];
	asprintf(&str, "%-*s    %-*s\n", (int)l[0], key, (int)l[1], v);
	qbuf_add(buf, str);
	ft_strdel(&str);
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

static int		print_hash(t_proc *p, t_hdict *dict)
{
	size_t		len[2];
	t_qbuf		*buf;
	void		*arg;
	char		*str;

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
	p->data.out = list_create(qbuf_del(&buf));
	return (0);
}

//int				ft_hash(t_proc *p, t_ctx *ctx)
//{
//	p->type = BUILTIN;
//
//	if (ctx->hash->count == 0)
//	{
//		p->data.out = list_create(ft_strdup("121sh: hash empty\n"));
//		return (0);
//	}
//	return (print_hash(p, ctx->hash));
//}

int					ft_hash(t_proc *p, t_ctx *ctx)
{
	int				i;
	int				j;
	int				f;
	int				ret;
	char			*str;

	p->type = BUILTIN;
	i = 1;
	f = 0;
	ret = 0;
	while (p->argv[i] != NULL)
	{
		if (p->argv[i][0] == '-')
		{
			j = 1;
			while (p->argv[i][j] != '\0')
			{
				if (p->argv[i][j] == 'r')
					f |= BU_H_CLR;
				else if (p->argv[i][j] == 'p')
					return (lhash_inh(p, ctx, i, j));
				else if (p->argv[i][j] == 'd' && (f & BU_H_PRT) == 0)
					f |= BU_H_DEL;
				else if (p->argv[i][j] == 't')
					f = (f & ~BU_H_DEL) | BU_H_PRT;
				else if (p->argv[i][j] == 'l')
					f |= BU_H_LST;
				else
				{
					asprintf(&str, "221sh: hash: -%c: invalid option\n%s",
								p->argv[i][j], BU_H_USAGE_);
					p->data.out = list_create(str);
					return (1);
				}
				j++;
			}
		}
		else
			break ;
		i++;
	}
	if (f & BU_H_CLR)
		hash_empty(ctx->hash, &ft_memdel);
	if (f & BU_H_DEL)
		ret |= (lhash_del(p, ctx, i));
	else if (f & BU_H_PRT)
		ret |= (lhash_prt(p, ctx, i));
	if (f == 0 || (f & BU_H_LST) == BU_H_LST)
		print_hash(p, ctx->hash);
	return (ret);
}
