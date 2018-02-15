/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_assignments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 14:38:09 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/15 16:54:20 by vbastion         ###   ########.fr       */
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

void					handle_assign(char ***astrenv, t_asmt *asmts,
										int *locpath)
{
	int					i;
	char				*str;

	*locpath = 0;
	while (asmts != NULL)
	{
		*locpath |= ft_strcmp("PATH", asmts->key) == 0;
		str = ft_strjoinc(asmts->key, asmts->value, '=');
		if ((i = ft_astr_getkey(*astrenv, asmts->key,
								ft_strlen(asmts->key))) != -1)
		{
			ft_strdel((*astrenv) + i);
			(*astrenv)[i] = str;
		}
		else
			ft_astr_append(astrenv, str);
		asmts = asmts->next;
	}
}
