/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:12:24 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/19 18:11:54 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	errno is only used to prevent race condition.
*/

#include <errno.h>

int						job_pipe(t_job *j, t_ctx *ctx)
{
	pid_t				pid;
	int					ret;

	if ((pid = fork()) < 0)
		return (1);
	else if (pid != 0)
	{
		j->pgid = pid;
		if ((ret = setpgid(pid, pid)) != 0 && errno != ESRCH)
			perror("GROBEN ERROREN in job_pipe setpgid");
		t_proc *p = j->procs;
		while (p != NULL)
		{
			if (p->next == NULL)
				p->pid = pid;
			p = p->next;
		}
	}
	else
	{
		j->pgid = getpid();
		if ((ret = setpgid(j->pgid, j->pgid)) != 0 && errno != ESRCH)
			perror("GROBEN ERROREN in job_pipe setpgid");
		exec_pipe(j, ctx);
	}
	return (0);
}

int						job_exec(t_job *j, t_ctx *ctx)
{
	int					exp_err;

	if (j == NULL)
		return (0);
	if (j->parent == j)
		j->command = get_command(j);
	j->status = expand_job(j, ctx, &exp_err);
	if (j->parent->bg == 0)
		ctx->fg_job = j;
	if (exp_err == 0 && job_pipe(j, ctx) == 1)
		return (1);
	if (j->parent->bg == 0 && exp_err)
		return (job_donext(j, ctx));
	else if (j->parent->bg == 0)
		return (job_next(j, ctx));
	return (0);
}
