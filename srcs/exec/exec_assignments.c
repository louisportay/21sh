/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_assignments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:38:09 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/16 16:07:16 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void					prefork_assign(t_ctx *ctx, t_asmt *asmt)
{
	int					pmod;

	handle_assign(&ctx->environ, asmt, &pmod);
	if (pmod)
	{
/*
**	UPDATE HASH
*/
		ctx->path = getpath(ctx->environ);
	}
}

void					handle_assign(char ***environ, t_asmt *asmts,
										int *locpath)
{
	(void)environ;
	(void)asmts;
	(void)locpath;
}	// CANDIDATE FOR DELETION, HERE FOR ARCHIVE PURPOSES

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
