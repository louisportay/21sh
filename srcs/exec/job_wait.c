/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:06:04 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/27 19:52:42 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int						job_wait(t_job *j)
{
	int					status;
	pid_t				pid;
	t_proc				*p;

	p = j->procs;
	while (p != NULL)
	{
		pid = waitpid(p->pid, &status, WUNTRACED);
		if (pid == -1)
		{
			perror("waitpid");
			return (-1);
		}
		p->status = status;
		if (WIFEXITED(status))
		{
			p->stopped = 1;
			j->status = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			p->completed = 1;
			dprintf(STDERR_FILENO, "%s (%d) stopped by sig(%d)\n",
					p->argv[0], pid, WTERMSIG(status));
		}
		p = p->next;
	}
	return (j->parent->status = j->status);
}

int						job_donext(t_job *j, t_ctx *ctx)
{
	int					ret;

	if (j->status == 0)
	{
		if (j->ok == NULL)
			return (j->status);
		else
		{
			if ((ret = job_exec(j->ok, j->parent->bg == 0, ctx)) == 0
				&& j->parent->status == 0)
				return (j->parent->status);
			else
				return (job_exec(j->err, j->parent->bg == 0, ctx));

		}
	}
	return (job_exec(j->err, 1, ctx));
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
			ft_putstr_fd("Kill error on kill zombies", STDERR_FILENO);
	}
}

int						job_putfg(t_job *j, int continued, t_ctx *ctx)
{
	int					ret;

	(void)continued;
//	if (ctx->fg_job != j->parent)
//		ctx->fg_job = j->parent;
//	j->running = 1;
	if (ctx->istty && (ret = tcsetpgrp(ctx->fd, j->pgid)) != 0)
		perror("tcsetpgrp - job_putfg");
//	while (j->completed != 1)
//		;
//	j->running = 0;
	job_wait(j);
	j->status = jc_pipestatus(j);
	j->parent->status = j->status;
	if (ctx->istty && (ret = tcsetpgrp(ctx->fd, ctx->pgid)) != 0)
		perror("tcsetpgrp");
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
