/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 14:35:53 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/11 17:35:44 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int					ft_fg(t_proc *p, t_ctx *ctx)
{
	size_t			i;
	t_job			*j;

	p->type = BU_STR;
	j = NULL;
	if (p->argv[1] == NULL)
		j = (ctx->bgs == NULL) ? NULL : (t_job *)ctx->bgs->content;
	else
		j = jc_jobspec(p, ctx);
	if (j != NULL)
	{
		i = jc_findid(ctx, j);
		j->stopped = 0;
		p = j->procs;
		while (p != NULL)
		{
			p->stopped = 0;
			p = p->next;
		}
		j->parent->stopped = 0;
		kill(-j->pgid, SIGCONT);
		job_putfg(j, ctx);
	}
	return (0);
}
