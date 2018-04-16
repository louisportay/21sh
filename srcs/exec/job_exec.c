/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:12:24 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/09 20:55:46 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int						job_exec(t_job *j, t_ctx *ctx)
{
	int					exp_err;

	if (j == NULL)
		return (0);
	j->command = get_command(j);
	while ((j->parent->status & JOB_DON) == 0)
	{
		j->status = expand_job(j, ctx, &exp_err);
		if (job_exec_loop(&j, ctx, exp_err) == 1)
			return (1);
	}
	if (ctx->last_argv != NULL)
		ft_strdel(&ctx->last_argv);
	ctx->last_argv = job_last_argv(j);
	return (0);
}
