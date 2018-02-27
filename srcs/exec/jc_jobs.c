/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_jobs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 10:29:44 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/27 11:37:28 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_job					*jc_getchild(t_job *j, pid_t pid, t_job **child)
{
	t_proc				*p;
	t_job				*ret_j;

	p = j->procs;
	while (p != NULL)
	{
		if (p->pid == pid)
		{
			*child = j;
			return (j->parent);
		}
		p = p->next;
	}
	if (j->ok != NULL && (ret_j = jc_getchild(j->ok, pid, child)) != NULL)
		return (j->parent);
	else if (j->err != NULL && (ret_j = jc_getchild(j->err, pid, child)) != NULL)
		return (j->parent);
	return (NULL);
}

t_job					*jc_getparent(t_ctx *ctx, pid_t pid, t_job **child)
{
	size_t				i;
	t_job				*j;

	if (ctx->fg_job != NULL && jc_getchild(ctx->fg_job, pid, child) != NULL)
		return (ctx->fg_job);
	i = 0;
	while (i < ctx->bg_cnt)
	{
		if (ctx->bg_jobs[i] != NULL
			&& (j = jc_getchild(ctx->bg_jobs[i], pid, child)) != NULL)
			return (j);
		i++;
	}
	dprintf(STDERR_FILENO, "Could not retrieve data for pid(%d)\n", pid);
	return (NULL);
}
