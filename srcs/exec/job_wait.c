/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:06:04 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/24 18:35:14 by vbastion         ###   ########.fr       */
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

/*
**	if (j->parent != NULL)
**		j->parent->status = j->parent;
**	if (j->status == 0)
**
**	while (1)
**	{
**		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
**		if (pid == -1)
**		{
**			perror("waitpid");
**			return ;
**		}
**		if (proc_chgstat(j, pid, status)
**			|| job_stopped(j)
**			|| job_completed(j))
**		{
**			// EXECUTE NEXT IN TREE
**			break ;
**		}
**	}
*/

int						job_donext(t_job *j, t_ctx *ctx)
{
	int					ret;

	if (j->status == 0)
	{
		ret = job_exec(j->ok, 1, ctx);
		if (ret == 0 && j->parent->status == 0)
			return (0);
		else
			return (job_exec(j->err, 1, ctx));
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
	int					status;

	if ((ret = tcsetpgrp(ctx->fd, j->pgid)) != 0)
		perror("tcsetpgrp");
	(void)continued;
	status = job_wait(j);
	if ((ret = tcsetpgrp(ctx->fd, ctx->pgid)) != 0)
		perror("tcsetpgrp");
	return (status);
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
