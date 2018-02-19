/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_setenv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:25:12 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/19 22:15:50 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void			update_env(char ***env, char *key, int end)
{
	int				i;

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

static int			is_sane(char *str, int *end)
{
	int				i;

	if ((*end = ft_strindex(str, '=')) == -1 && *end == 0)
		return (0);
	if (ft_isalpha(str[0]) == 0 && str[0] != '_')
		return (0);
	i = 1;
	while (i < *end)
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int			add_error(t_proc *p, t_list *lsts[2], char *str, int end)
{
	char			*lstr;

	asprintf(&lstr, "221sh: setenv: '%*s': not a valid identifier\n",
				(int)(end == -1 ? ft_strlen(str) : end), str);
	lsts[2] = list_create(str);
	ft_list_insert(&p->data.out, lsts, lsts[1]);
	return (1);
}
int					ft_setenv(t_proc *p, t_ctx *ctx)
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
			ret |= add_error(p, lsts, p->argv[i], j);
		i++;
	}
	return (0);
}
