/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_kill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 14:35:52 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/25 20:35:16 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void			lmultiargs(t_proc *p, t_ctx *ctx)
{
	int				i;
	t_job			*j;

	i = 0;
	while (p->argv[i] != NULL)
	{
		if ((j = jc_jobspec(p, "kill", p->argv[i], ctx)) != NULL)
			kill(-j->pgid, SIGTERM);
		i++;
	}
}

int					ft_kill(t_proc *p, t_ctx *ctx, int pipeline)
{
	char			*str;

	if (pipeline)
	{
		p->type = BU_STR;
		p->data.str = ft_strdup("221sh: kill: no job control\n");
		return (1);
	}
	p->type = BUILTIN;
	if (p->argv[1] == NULL)
	{
		if (ctx->bgs == NULL)
		{
			ft_asprintf(&str, BU_JOB_ERR, "kill", BU_JOB_NO);
			p->data.out = list_create(str);
		}
		else
			kill(-(((t_job *)ctx->bgs->content)->pgid), SIGTERM);
	}
	else
		lmultiargs(p, ctx);
	return (0);
}
