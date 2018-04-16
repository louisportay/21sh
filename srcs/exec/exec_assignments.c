/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_assignments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:38:09 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/01 17:43:02 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void				l_export(t_ctx *ctx, t_asmt *asmt)
{
	int					i;
	char				*str;

	if ((i = ft_astr_getlowkey(ctx->locals, asmt->key)) != -1)
	{
		str = ft_astr_remove_at(&ctx->locals, i);
		ft_strdel(&str);
	}
	str = ft_strjoinc(asmt->key, asmt->value, '=');
	if ((i = ft_astr_getlowkey(ctx->environ, asmt->key)) != -1)
	{
		ft_strdel(ctx->environ + i);
		ctx->environ[i] = str;
	}
	else
		ft_astr_append(&ctx->environ, str);
}

static void				l_update(t_ctx *ctx, t_asmt *asmt)
{
	int					i;

	if ((i = ft_astr_getlowkey(ctx->environ, asmt->key)) != -1)
	{
		ft_strdel(ctx->environ + i);
		ctx->environ[i] = ft_strjoinc(asmt->key, asmt->value, '=');
	}
	else
		astr_env_replace(&ctx->locals, asmt->key, asmt->value);
}

void					prefork_assign(t_ctx *ctx, t_asmt *asmt)
{
	int					pmod;
	int					export;

	export = ctx->set & BU_SET_EXPOR;
	pmod = 0;
	while (asmt != NULL)
	{
		pmod |= ft_strcmp(asmt->key, "PATH") == 0;
		if (export)
			l_export(ctx, asmt);
		else
			l_update(ctx, asmt);
		asmt = asmt->next;
	}
	if (pmod)
		path_reset(ctx, 1);
}

int						proc_update_env(t_proc *p)
{
	int					i;
	char				*str;
	int					mod;
	t_asmt				*a;

	mod = 0;
	a = p->asmts;
	while (a != NULL)
	{
		mod |= ft_strcmp("PATH", a->key) == 0;
		str = ft_strjoinc(a->key, a->value, '=');
		if ((i = ft_astr_getkey(p->env, a->key,
								ft_strlen(a->key))) != -1)
		{
			ft_strdel(p->env + i);
			p->env[i] = str;
		}
		else
			ft_astr_append(&p->env, str);
		a = a->next;
	}
	return (mod);
}
