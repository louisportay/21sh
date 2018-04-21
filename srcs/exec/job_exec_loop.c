/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_exec_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 20:48:08 by lportay           #+#    #+#             */
/*   Updated: 2018/04/21 15:42:11 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include <errno.h>

static void				l_handle_proc_status(t_proc *p, int status)
{
	if (WIFEXITED(status))
		p->status = WEXITSTATUS(status) | JOB_CMP;
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGPIPE)
		{
			waitpid(p->pid, &status, WUNTRACED);
			p->status = (p->status & 0xFF) | JOB_CMP;
			return ;
		}
		p->status = WTERMSIG(status);
		waitpid(p->pid, &status, WUNTRACED);
		p->status = (p->status & 0xFF) | JOB_SIG | JOB_CMP;
	}
	else
		ft_printf("Received unhandled status\n");
}

static int				l_wait_for_job(t_job *j)
{
	t_proc				*p;
	int					status;
	pid_t				pid;

	status = 0;
	p = j->procs;
	while (p != NULL)
	{
		while ((p->status & JOB_CMP) == 0)
		{
			pid = waitpid(p->pid, &status, 0);
			if (pid < 0 && errno != ECHILD)
				ft_dprintf(STDERR_FILENO, "Critical pid error.\n");
			l_handle_proc_status(p, status);
		}
		if (p->next == NULL)
			j->status = (p->status & 0xFF) | JOB_CMP;
		p = p->next;
	}
	return (0);
}

static int				wait_err(t_job *j)
{
	int					status;

	waitpid(j->procs->pid, &status, WUNTRACED);
	j->status = JOB_CMP | (-42 & 0xFF);
	return (1);
}

int						job_exec_loop(t_job **job, t_ctx *ctx)
{
	t_job				*j;
	t_job				*n;
	int					ret;

	j = *job;
	if ((ret = ((j->procs->next != NULL) ?
					job_pipe(j, ctx) : job_one(j, ctx))) == 1)
		return (1);
	else if (ret == -1)
		return (wait_err(j));
	l_wait_for_job(j);
	if ((n = job_getnextexec(j)) == NULL)
		j->parent->status = (JOB_DON | (j->status & 0xFF));
	else
		j = n;
	*job = j;
	return (0);
}
