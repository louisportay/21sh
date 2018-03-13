/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 14:04:15 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/13 12:44:17 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void					jc_updateproc(t_job *j, t_proc *p, int status)
{
	if (WIFEXITED(status))
	{
		p->completed = 1;
		p->status = WEXITSTATUS(status);
	}
	else if (WIFSTOPPED(status))
	{
		p->stopped = 1;
		j->stopped = 1;
		kill(-j->pgid, SIGTSTP);
	}
	else if (WIFSIGNALED(status))
	{
		p->completed = 1;
		j->parent->status = WTERMSIG(status);
		dprintf(STDERR_FILENO, "%d: Terminated by signal %d.\n", (int)p->pid,
				j->parent->status);
		j->parent->done = 1;
	}
	else
		printf("Received unhandled status\n");
}

static int				lstopall(t_job *j)
{
	t_proc				*p;

	j->completed = 0;
	j->stopped = 1;
	j->parent->stopped = 1;
	p = j->procs;
	while (p != NULL)
	{
		p->stopped = 1;
		p = p->next;
	}
	return (1);
}

static int				lwaitpid(t_job *j, t_proc *p)
{
	pid_t				pid;
	int					status;

	if (p->completed == 1)
		;
	else if ((pid = waitpid(p->pid, &status, WNOHANG | WUNTRACED)) > 0)
		jc_updateproc(j, p, status);
	else if (pid == 0)
		;
	else if (pid == -1)
		return (-1);
	return (0);
}

int						jc_updatepipe(t_job *j)
{
	t_proc				*p;
	int					completed;

	if (j == NULL)
		return (0);
	p = j->procs;
	completed = 1;
	while (p != NULL)
	{
		if (lwaitpid(j, p) == -1)
			return (-1);
		completed &= p->completed;
		if (p->stopped)
			return (lstopall(j));
		j->status = p->status;
		p = p->next;
	}
	if (completed == 1)
		j->completed = 1;
	return (j->status);
}

void					jc_updatebg(t_ctx *ctx)
{
	size_t				i;

	i = 0;
	while (i < ctx->bg_cnt)
	{
		jc_updatepipe(ctx->bg_jobs[i]);
		i++;
	}
}
