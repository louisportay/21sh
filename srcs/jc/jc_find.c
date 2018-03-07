/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_find.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 14:48:22 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/07 18:28:42 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	Looks for a pid in given pipeline
**	RETURN 1 IF success ELSE 0
*/

int						jc_procfind(t_job *j, pid_t pid)
{
	t_proc				*p;

	if (j == NULL)
		return (0);
	p = j->procs;
	while (p != NULL)
	{
		if (p->pid == pid)
			return (1);
		p = p->next;
	}
	return (0);
}

/*
**	Looks for process in pipes contained in `ctx->bg_jobs` job array
**	RETURN index IF found ELSE -1
*/

int						jc_jobfind(t_ctx *ctx, pid_t pid)
{
	size_t				i;

	i = 0;
	while (i < ctx->bg_cnt)
	{
		if (ctx->bg_jobs[i] != NULL
			&& jc_procfind(ctx->bg_jobs[i], pid) != 0)
			return (i);
		i++;
	}
	return (-1);
}
