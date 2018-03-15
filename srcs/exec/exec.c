/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:30:05 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/15 17:47:35 by vbastion         ###   ########.fr       */
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
	int					was_bg;
	size_t				id;

	bg[0] = NULL;
	ctx = get_ctxaddr();
	update_tty(ctx, 1);
	signal(SIGCHLD, SIG_DFL);
	while (jobs != NULL)
	{
		tmp = jobs;
		jobs = jobs->next;
		tmp->next = NULL;
		{	/*	Add old job deletion if not empty and on loop end	*/	}
		was_bg = tmp->parent->bg;
		if (tmp->parent->bg == 0)
			ctx->fg_job = tmp;
		job_exec(tmp, ctx);
		id = (size_t)-1;
		if (tmp->parent->bg != 0)
			id = jc_addtobg(ctx, tmp);
		else
			ctx->fg_job = NULL;	//	TO BE DELETED
		if (was_bg && id != (size_t)-1)
			printf("[%zu] %d\n", id + 1, tmp->pgid);
	}
	jc_updatebg(ctx);
	signal(SIGCHLD, &jc_signal);
	update_tty(ctx, 0);
	return (0);
}
