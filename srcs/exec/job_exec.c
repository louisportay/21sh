/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:12:24 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/20 18:39:01 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int						job_exec(t_job *j, t_ctx *ctx)
{
	if (j == NULL)
		return (0);
	while ((j->parent->status & JOB_DON) == 0)
	{
		j->status = expand_job(j, ctx);
		if (job_exec_loop(&j, ctx) == 1)
			return (1);
	}
	if (ctx->last_argv != NULL)
		ft_strdel(&ctx->last_argv);
	ctx->last_argv = job_last_argv(j);
	return (0);
}
