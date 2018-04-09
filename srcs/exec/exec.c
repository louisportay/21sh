/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:30:05 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/09 20:14:39 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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
	signal(SIGINT, SIG_IGN);
	while (jobs != NULL)
	{
		tmp = jobs;
		jobs = jobs->next;
		tmp->next = NULL;
		job_exec(tmp, ctx);
		ctx->last_ret = tmp->parent->status & 0xFF;
		job_safeclear(&tmp->parent);
		dup2(ctx->std_fd[1], STDOUT_FILENO);
		dup2(ctx->std_fd[0], STDIN_FILENO);
	}
	signal(SIGINT, &sighand_int);
	update_tty(ctx, 0);
	return (0);
}
