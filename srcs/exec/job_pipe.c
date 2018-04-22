/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 11:32:11 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/22 13:06:16 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include <errno.h>

int						job_setpgid(pid_t pid, pid_t pgid)
{
	if (setpgid(pid, pgid) == -1 && errno != EACCES)
	{
		if (errno == EINVAL)
			ft_putstr_fd("42sh: setpgid: Invalid pgid\n", STDERR_FILENO);
		else if (errno == EPERM)
			ft_putstr_fd("42sh: setpgid: Missing permissions\n", STDERR_FILENO);
		else if (errno == ESRCH)
			ft_dprintf(STDERR_FILENO, "42sh: setpgid: No matching pid(%d)\n",
						pid);
		return (-1);
	}
	return (0);
}

int						job_setpgrp(pid_t pgid)
{
	t_ctx				*ctx;

	ctx = get_ctxaddr();
	if (ctx->istty == 0)
		return (0);
	else if (tcsetpgrp(ctx->term_fd, pgid) == -1)
	{
		ft_putstr_fd("42sh: Controlling terminal error\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

static int				l_job_pipe(t_job *j, pid_t pid)
{
	j->pgid = pid;
	if (job_setpgid(pid, pid) == -1)
		return (-1);
	else if (job_setpgrp(pid) == -1)
		return (-1);
	return (0);
}

int						job_pipe(t_job *j)
{
	pid_t				pid;

	if ((pid = fork()) < 0)
		return (1);
	else if (pid != 0)
		return (l_job_pipe(j, pid));
	else
		exec_pipe(j);
	return (0);
}
