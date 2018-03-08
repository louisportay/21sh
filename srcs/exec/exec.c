/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:30:05 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/08 17:28:25 by vbastion         ###   ########.fr       */
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
	t_job				*bg[2];

	bg[0] = NULL;
	ctx = get_ctxaddr(NULL);
	update_tty(ctx, 1);
	signal(SIGCHLD, SIG_DFL);
	while (jobs != NULL)
	{
		tmp = jobs;
		jobs = jobs->next;
		tmp->next = NULL;
		{	/*	Add old job deletion if not empty and on loop end	*/	}
		if (tmp->parent->bg == 0)
			ctx->fg_job = tmp;
		job_exec(tmp, ctx);
		if (tmp->parent->bg)
			job_ctxinsert(tmp, ctx);
		else
			ctx->fg_job = NULL;	//	TO BE DELETED
	}
	jc_updatebg(ctx);
	signal(SIGCHLD, &jc_signal);
	update_tty(ctx, 0);
	jc_print(ctx, 0, 0);
	return (0);
}
