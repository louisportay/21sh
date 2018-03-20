/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:30:05 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/20 19:42:58 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void				update_tty(t_ctx *ctx, int old)
{
	int					ret;

	if (ctx->istty == 0)
		return ;
	ret = tcsetattr(ctx->fd, TCSADRAIN, old ? &ctx->oldtios : &ctx->tios);
	if (ret != 0)
		perror(old ? "tcsetattr reset" : "tcsetattr set");
}

int						exec(t_job *jobs)
{
	t_ctx				*ctx;
	t_job				*tmp;
	int					was_bg;
	size_t				id;

	ctx = get_ctxaddr();
	update_tty(ctx, 1);
	signal(SIGCHLD, SIG_IGN);
	while (jobs != NULL)
	{
		tmp = jobs;
		jobs = jobs->next;
		tmp->next = NULL;
		was_bg = tmp->parent->bg;
		if (tmp->parent->bg == 0)
			ctx->fg_job = tmp;
		job_exec(tmp, ctx);
		id = (size_t)-1;
		if (tmp->parent->bg != 0)
			id = jc_addtobg(ctx, tmp);
		else
			job_safeclear(&tmp->parent);
		if (was_bg && id != (size_t)-1)
			printf("[%zu] %d\n", id + 1, tmp->pgid);
	}
	signal(SIGCHLD, &jc_signal);
	update_tty(ctx, 0);
	return (0);
}
