/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 14:35:55 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/11 17:15:14 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

size_t				jc_findid(t_ctx *ctx, t_job *j)
{
	size_t			i;

	i = 0;
	while (i < ctx->bg_cnt)
	{
		if (ctx->bg_jobs[i] == j)
			return (i);
		i++;
	}
	return ((size_t)-1);
}

int					ft_bg(t_proc *p, t_ctx *ctx)
{
	t_job			*j;
	size_t			i;

	p->type = BU_STR;
	j = NULL;
	if (p->argv[1] == NULL)
		j = (ctx->bgs == NULL) ? NULL : (t_job *)ctx->bgs->content;
	else
		j = jc_jobspec(p, ctx);
	if (j != NULL)
	{
		i = jc_findid(ctx, j);
		printf("[%zu]%-2c%s &\n", i + 1, jc_getstatus(j), j->parent->command);
		j->stopped = 0;
		t_proc *p = j->procs;
		while (p != NULL)
		{
			p->stopped = 0;
			p = p->next;
		}
		j->parent->stopped = 0;
		kill(-j->pgid, SIGCONT);
	}
	return (0);
}
