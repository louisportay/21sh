/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:06:04 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/14 17:36:59 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void					job_wait(t_job *j)
{
	int					status;
	pid_t				pid;

	while (1)
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
		if (pid == -1)
		{
			perror("waitpid");
			return ;
		}
		if (proc_chgstat(j, pid, status)
			|| job_stopped(j)
			|| job_completed(j))
		{
			// EXECUTE NEXT IN TREE
			break ;
		}
	}
}

void					job_putbg(t_job *j, int continued)
{
	if (continued != 0)
	{
		if (kill(-j->pgid, SIGCONT) < 0)
			ft_putstr_fd("Kill error on kill zombies", STDERR_FILENO);
	}
}

void					job_putfg(t_job *j, int continued, t_ctx *ctx)
{
	int ret;

	if ((ret = tcsetpgrp(ctx->fd, j->pgid)) != 0)
		perror("tcsetpgrp");
	(void)continued;
//	if (continued != 0)
//	{
//		if ((ret = tcsetattr(ctx->fd, TCSADRAIN, &j->tmodes)) != 0)
//			perror("tcsetattr");
//		if (kill(-j->pgid, SIGCONT) < 0)
//			ft_putstr_fd("Kill error on kill zombies", STDERR_FILENO);
//	}
	job_wait(j);
	if ((ret = tcsetpgrp(ctx->fd, ctx->pgid)) != 0)
		perror("tcsetpgrp");
}
