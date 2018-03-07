/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:30:05 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/07 18:30:33 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

//	static void				job_sort(t_job **j, t_job *fg[2], t_job *bg[2])
//	{
//		t_job				*tj;
//	
//		tj = *j;
//		*j = tj->next;
//		tj->next = NULL;
//		if (tj->bg)
//			job_insert(bg, bg + 1, tj);
//		else
//			job_insert(fg, fg + 1, tj);
//	}

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
		if (tmp->bg == 0)
			ctx->fg_job = tmp;
		job_exec(tmp, tmp->bg == 0, ctx);
		if (tmp->bg)
			job_ctxinsert(tmp, ctx);
	}
	for (size_t i = 0; i < ctx->bg_cnt; i++)
		jc_updatepipe(ctx->bg_jobs[i]);
	jc_print(ctx);
	jc_clear(ctx);
	update_tty(ctx, 0);
	signal(SIGCHLD, &jc_signal);
	return (0);
}
