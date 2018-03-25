/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_addenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:25:12 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/25 13:52:39 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void			update_env(char ***env, char *key, int end, char ***locals)
{
	int				i;
	int				lpos;

	if (ft_strindex(key, '=') == -1
		&& (lpos = ft_astr_getkey(*locals, key, ft_strlen(key))) != -1)
	{
		ft_astr_append(env, (*locals)[lpos]);
		ft_astr_remove_at(locals, lpos);
		return ;
	}
	if ((i = ft_astr_getkey(*env, key, end)) != -1)
	{
		if (ft_strcmp(key, (*env)[i]) == 0)
			return ;
		ft_strdel((*env) + i);
		(*env)[i] = ft_strdup(key);
	}
	else
		ft_astr_append(env, ft_strdup(key));
}

static void			update_locals(char ***locals, char *key, int end)
{
	int				k;
	char			*tmp;

	if ((k = ft_astr_getkey(*locals, key, end)) != -1)
	{
		tmp = ft_astr_remove_at(locals, k);
		ft_strdel(&tmp);
	}
}

static int			add_error(t_proc *p, t_list *lsts[2], char *str, char *bu)
{
	char			*lstr;
	int				i;
	t_list			*l;

	if ((i = ft_strindex(str, '=')) == -1)
		i = ft_strlen(str);
	asprintf(&lstr, "221sh: %s: '%*s': not a valid identifier\n", bu, i, str);
	l = list_create(lstr);
	ft_list_insert(&p->data.out, lsts, l);
	return (1);
}

int					modenv(t_proc *p, t_ctx *ctx, char *name)
{
	int				i;
	int				j;
	int				ret;
	t_list			*lsts[2];
	int				pmod;

	pmod = 0;
	p->type = BUILTIN;
	i = 1;
	ret = 0;
	while (p->argv[i] != NULL)
	{
		if (is_sane(p->argv[i], &j))
		{
			pmod |= ft_strcmp(p->argv[i], "PATH") == 0;
			update_env(&ctx->environ, p->argv[i], j, &ctx->locals);
			update_locals(&ctx->locals, p->argv[i], j);
		}
		else
			ret |= add_error(p, lsts, p->argv[i], name);
		i++;
	}
	if (pmod)
		path_reset(ctx, 1);
	return (0);
}
