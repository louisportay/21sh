/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_addenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:25:12 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/04 17:19:06 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void			linloc(t_ctx *ctx, char *key, int pos, int eq)
{
	char			*str;

	str = ft_astr_remove_at(&ctx->locals, pos);
	if (eq)
	{
		ft_astr_append(&ctx->environ, ft_strdup(key));
		ft_strdel(&str);
	}
	else
		ft_astr_append(&ctx->environ, str);
}

static void			linenv(t_ctx *ctx, char *key, int pos, int eq)
{
	if (eq)
	{
		ft_strdel(ctx->environ + pos);
		ctx->environ[pos] = ft_strdup(key);
	}
	return ;
}

static void			update_ctx(t_ctx *ctx, char *key)
{
	int				i;
	int				eq;
	int				penv;
	int				ploc;

	if ((i = ft_strindex(key, '=')) == -1)
	{
		eq = 0;
		i = ft_strlen(key);
	}
	else
		eq = 1;
	penv = ft_astr_getlowkey(ctx->environ, key);
	ploc = ft_astr_getlowkey(ctx->locals, key);
	if (ploc != -1)
		linloc(ctx, key, ploc, eq);
	else if (penv != -1)
		linenv(ctx, key, penv, eq);
	else
		ft_astr_append(&ctx->environ, ft_strdup(key));
}

static int			add_error(char *str, char *bu)
{
	int				i;

	if ((i = ft_strindex(str, '=')) == -1)
		i = ft_strlen(str);
	ft_dprintf(STDERR_FILENO, "21sh: %s: '%*s': not a valid identifier\n",
				bu, i, str);
	return (1);
}

int					modenv(t_proc *p, t_ctx *ctx, char *name)
{
	int				i;
	int				j;
	int				k;
	int				ret;
	int				pmod;

	pmod = 0;
	p->type = BUILTIN;
	i = 1;
	ret = 0;
	while (p->argv[i] != NULL)
	{
		if (is_sane(p->argv[i], &j))
		{
			k = ft_strindex(p->argv[i], '=');
			k = (k == -1) ? ft_strlen(p->argv[i]) : k;
			pmod |= ft_strncmp(p->argv[i], "PATH", k) == 0;
			update_ctx(ctx, p->argv[i]);
		}
		else
			ret |= add_error(p->argv[i], name);
		i++;
	}
	if (pmod)
		path_reset(ctx, 1);
	return (0);
}
