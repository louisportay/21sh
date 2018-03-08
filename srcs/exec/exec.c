/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:30:05 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/08 14:27:09 by vbastion         ###   ########.fr       */
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
		job_exec(tmp, ctx);
		if (tmp->bg)
			job_ctxinsert(tmp, ctx);
	}
	jc_updatebg(ctx);
	signal(SIGCHLD, &jc_signal);
	update_tty(ctx, 0);
	jc_print(ctx);
	return (0);
}
