/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 14:05:13 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/21 16:20:13 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static t_blt			get_proc_blt(char *name, t_hdict *blts)
{
	t_hentry		*e;

	if (name == NULL)
		return (NULL);
	if ((e = hash_lookup(blts, name)) != NULL)
		return ((t_blt)e->content);
	return (NULL);
}

static void				test_env_builtin(t_proc *p)
{
	if (ft_strcmp("env", p->argv[0]) == 0)
	{
		// DO p->env MODS
		// SHIFT p->args TO theorical binary
		// SET p->type AS BINARY
	}
}

int						prepare_fork(t_proc *p, t_ctx *ctx)
{
	t_blt				blt;
	int					pmod;

	p->env = ft_astr_dup(ctx->environ);
	pmod = (p->asmts != NULL && p->argv[0] != NULL) ? proc_update_env(p) : 0;
	test_env_builtin(p);
	if ((blt = get_proc_blt(p->argv[0], ctx->builtins)) != NULL)
		p->status = blt(p, ctx);
	else
	{
		if ((p->data.path = proc_path(p, ctx, pmod)) == NULL)
			p->type = EXERR;
	}
	return (0);
}
