/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:06:04 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/09 18:07:20 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int						job_donext(t_job *j, t_ctx *ctx)
{
	int					ret;

	if (j->status == 0)
	{
		if (j->ok == NULL)
			return (j->status);
		else
		{
			if ((ret = job_exec(j->ok, ctx)) == 0
					&& j->parent->status == 0)
				return (j->parent->status);
			else
				return (job_exec(j->err, ctx));

		}
	}
	if (j->err != NULL)
		return (j->status = job_exec(j->err, ctx));
	return (j->status);
}

int						job_next(t_job *j, t_ctx *ctx)
{
	j->status = job_putfg(j, 0, ctx);
	return (job_donext(j, ctx));
}

void					job_putbg(t_job *j, int continued)
{
	if (continued != 0)
	{
		if (kill(-j->pgid, SIGCONT) < 0)
			ft_putstr_fd("Error on sending SIGCONT to group\n", STDERR_FILENO);
	}
}

int						job_putfg(t_job *j, int continued, t_ctx *ctx)
{
	int					ret;

	(void)continued;
	if (ctx->istty && (ret = tcsetpgrp(ctx->fd, j->pgid)) != 0)
		perror("tcsetpgrp - job_putfg");
	//	if (j->completed == 0 && j->stopped == 0)
	//	{
	ctx->fg_job = j;
	signal(SIGCHLD, &jc_signal);
	while (j->completed != 1 && j->stopped != 1)
	{
		jc_updatebg(ctx);
		jc_updatepipe(j);
	}
	if (j->stopped)
		jc_addtobg(ctx, j);
	//	}
	if (ctx->istty && (ret = tcsetpgrp(ctx->fd, ctx->pgid)) != 0)
		perror("tcsetpgrp");
	signal(SIGCHLD, SIG_IGN);
	return (j->status);
}

/*
 **	if (continued != 0)
 **	{
 **		if ((ret = tcsetattr(ctx->fd, TCSADRAIN, &j->tmodes)) != 0)
 **			perror("tcsetattr");
 **		if (kill(-j->pgid, SIGCONT) < 0)
 **			ft_putstr_fd("Kill error on kill zombies", STDERR_FILENO);
 **	}
 */
