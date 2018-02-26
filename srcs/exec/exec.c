/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:30:05 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/26 18:41:33 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void				job_sort(t_job **j, t_job *fg[2], t_job *bg[2])
{
	t_job				*tj;

	tj = *j;
	*j = tj->next;
	tj->next = NULL;
	if (tj->bg)
		job_insert(bg, bg + 1, tj);
	else
		job_insert(fg, fg + 1, tj);
}

static void				update_tty(t_ctx *ctx, int old)
{
	int					ret;

	if (ctx->istty == 0)
		return ;
	ret = tcsetattr(ctx->fd, TCSADRAIN, old ? &ctx->oldtios : &ctx->tios);
	if (ret != 0)
		perror(old ? "tcsetattr reset" : "tcsetattr set");
}

int						exec(t_job **jobs)
{
	t_ctx				*ctx;
	t_job				*bg[2];
	t_job				*fg[2];
	t_job				*j;

	bg[0] = NULL;
	fg[0] = NULL;
	ctx = get_ctxaddr(NULL);
	j = *jobs;
	update_tty(ctx, 1);
	while (j != NULL)
	{
		job_exec(j, j->bg == 0, get_ctxaddr(NULL));
		job_sort(&j, fg, bg);
	}
	update_tty(ctx, 0);
	*jobs = fg[0];
	return (0);
}
