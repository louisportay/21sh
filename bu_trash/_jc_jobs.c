/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 10:29:44 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/27 15:57:12 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static t_job			*jc_get(t_job *j, pid_t pid)
{
	t_proc				*p;
	t_job				*ret_j;
	t_job				*ok;

	p = j->procs;
	while (p != NULL)
	{
		if (p->pid == pid)
			return (j);
		p = p->next;
	}
	ok = j->ok;
	while (ok != NULL)
	{
		if ((ret_j = jc_get(ok, pid)) != NULL)
			return (ret_j);
		ok = ok->ok;
	}
	if (j->err != NULL && (ret_j = jc_get(j->err, pid)) != NULL)
		return (ret_j);
	return (NULL);
}

t_job					*jc_getjob(t_ctx *ctx, pid_t pid)
{
	size_t				i;
	t_job				*j;

	if (ctx->fg_job != NULL && (j = jc_get(ctx->fg_job, pid)) != NULL)
		return (j);
	i = 0;
	while (i < ctx->bg_cnt)
	{
		if (ctx->bg_jobs[i] != NULL
			&& (j = jc_get(ctx->bg_jobs[i], pid)) != NULL)
			return (j);
		i++;
	}
	dprintf(STDERR_FILENO, "Could not retrieve data for pid(%d)\n", pid);
	return (NULL);
}
