/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:30:05 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/22 19:56:32 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void				update_tty(t_ctx *ctx, int old)
{
	if (ctx->istty == 0)
		return ;
	tcsetattr(STDIN_FILENO, TCSADRAIN, old ? &ctx->oldtios
												: &ctx->tios);
}

int						exec(t_job *jobs)
{
	t_ctx				*ctx;
	t_job				*tmp;

	ctx = get_ctxaddr();
	update_tty(ctx, 1);
	while (jobs != NULL)
	{
		tmp = jobs;
		jobs = jobs->forward;
		tmp->forward = NULL;
		job_exec(tmp, ctx);
		ctx->last_ret = tmp->parent->status & 0xFF;
		job_safeclear(&tmp->parent);
		dup2(ctx->std_fd[1], STDOUT_FILENO);
		dup2(ctx->std_fd[0], STDIN_FILENO);
	}
	if (ctx->istty && ctx->c_opt == 0
		&& tcsetpgrp(ctx->term_fd, ctx->pid) == -1)
	{
		ft_putstr_fd("42sh: could not control back\n", STDERR_FILENO);
		exit(-42);
	}
	update_tty(ctx, 0);
	return (0);
}
