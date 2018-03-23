/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_addenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:25:12 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/23 11:45:08 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char			*lgetval(char *key, int end)
{
	size_t			len;
	char			*ret;

	if (key[end] == '\0')
	{
		len = ft_strlen(key);
		ret = ft_strnew(len + 1);
		ft_strncpy(ret, key, len);
		ret[len] = '=';
		return (ret);
	}
	else
		return (ft_strdup(key));
}

static void			update_env(char ***env, char *key, int end)
{
	int				i;
	char			*val;

	val = lgetval(key, end);
	if ((i = ft_astr_getkey(*env, key, end)) != -1)
	{
		if (ft_strcmp(key, (*env)[i]) == 0)
			return ;
		ft_strdel((*env) + i);
		(*env)[i] = val;
	}
	else
		ft_astr_append(env, val);
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

	p->type = BUILTIN;
	i = 1;
	ret = 0;
	while (p->argv[i] != NULL)
	{
		if (is_sane(p->argv[i], &j))
		{
			update_env(&ctx->environ, p->argv[i], j);
			update_locals(&ctx->locals, p->argv[i], j);
		}
		else
			ret |= add_error(p, lsts, p->argv[i], name);
		i++;
	}
	return (0);
}
