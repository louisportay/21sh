/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 19:27:34 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/10 09:30:40 by lportay          ###   ########.fr       */
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
		hash_print(ctx->hash);
	return (ret);
}
