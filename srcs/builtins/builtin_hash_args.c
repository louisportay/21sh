/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 18:58:08 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/26 17:27:52 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int				l_isdir(char *path, t_proc *p)
{
	struct stat			stats;
	char				*str;
	t_list				*l;

	if (stat(path, &stats) != -1)
	{
		if (S_ISDIR(stats.st_mode))
		{
			ft_asprintf(&str, "221sh: hash: %s is a directory\n", path);
			l = list_create(str);
			if (p->data.out != NULL)
				ft_list_last(p->data.out)->next = l;
			else
				p->data.out = l;
			return (1);
		}
	}
	return (0);
}

static int				ladderr(t_proc *p)
{
	p->data.out = list_create(ft_strdup(BU_H_EPREQU));
	return (-1);
}

static char				*lnewval(t_proc *p, char *str, int *k, int newk)
{
	if (l_isdir(str, p))
		return (NULL);
	*k = newk;
	return (ft_strdup(str));
}

static int				lhash_inh(t_proc *p, t_ctx *ctx, int i, int j)
{
	char				*key;
	char				*value;
	int					k;

	if (p->argv[i][j + 1] != '\0')
	{
		if (p->argv[i + 1] == NULL)
			return (ladderr(p));
		if ((value = lnewval(p, p->argv[i] + j + 1, &k, i + 1)) == NULL)
			return (-1);
	}
	else
	{
		if (p->argv[i + 1] == NULL || p->argv[i + 2] == NULL)
			return (ladderr(p));
		if ((value = lnewval(p, p->argv[i + 1], &k, i + 2)) == NULL)
			return (-1);
	}
	while (p->argv[k + 1] != NULL)
		k++;
	key = ft_strdup(p->argv[k]);
	hash_add_or_mod(ctx->hash, key, value, &ft_memdel);
	return (0);
}

static int				lget_opt(t_proc *p, t_ctx *ctx, int i, int *f)
{
	int					j;
	char				*str;

	j = 1;
	while (p->argv[i][j] != '\0')
	{
		if (p->argv[i][j] == 'r')
			*f |= BU_H_CLR;
		else if (p->argv[i][j] == 'p')
			return (lhash_inh(p, ctx, i, j) == 0 ? -2 : -1);
		else if (p->argv[i][j] == 'd' && (*f & BU_H_PRT) == 0)
			*f |= BU_H_DEL;
		else if (p->argv[i][j] == 't')
			*f = (*f & ~BU_H_DEL) | BU_H_PRT;
		else if (p->argv[i][j] == 'l')
			*f |= BU_H_LST;
		else
		{
			ft_asprintf(&str, BU_H_EINVAL, p->argv[i][j], BU_H_USAGE_);
			p->data.out = list_create(str);
			return (-1);
		}
		j++;
	}
	return (0);
}

int						bu_hash_getopts(t_proc *p, t_ctx *ctx, int *i)
{
	int					f;
	int					t;

	f = 0;
	while (p->argv[*i] != NULL)
	{
		if (p->argv[*i][0] == '-')
		{
			if ((t = lget_opt(p, ctx, *i, &f)) < 0)
				return (t);
		}
		else
			break ;
		(*i)++;
	}
	return (f);
}
