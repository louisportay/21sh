/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 14:04:15 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/14 13:19:28 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void					jc_updateproc(t_job *j, t_proc *p, int status)
{
	if (WIFEXITED(status))
		p->status = WEXITSTATUS(status) | JOB_CMP;
	else if (WIFSTOPPED(status))
	{
		p->status |= JOB_STP;
		j->status |= JOB_STP;
		kill(-j->pgid, SIGTSTP);
	}
	else if (WIFSIGNALED(status))
	{
		p->status = (JOB_CMP | JOB_SIG) | (WTERMSIG(status) & 0xFF);
//		dprintf(STDERR_FILENO, "%d: Terminated by signal %d.\n", (int)p->pid,
//				j->parent->status & 0xFF);
		j->parent->status = p->status | JOB_DON;
		j->status = p->status | JOB_DON;
	}
	else
		printf("Received unhandled status\n");
}

static void				lstp(t_proc *p)
{
	p->status |= JOB_STP;
}

static int				lstopall(t_job *j)
{

	j->status = JOB_STP;
	j->parent->status |= JOB_STP;
	proc_foreach(j->procs, &lstp);
	return (1);
}

static int				lwaitpid(t_job *j, t_proc *p)
{
	pid_t				pid;
	int					status;

	if ((p->status & JOB_CMP) != 0)
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
		completed &= ((p->status & JOB_CMP) != 0);
		if (p->status & JOB_STP)
			return (lstopall(j));
		j->status = ((j->status & ~0xFF) | (p->status & 0xFF));
		p = p->next;
	}
	if (completed == 1)
		j->status |= JOB_CMP;
	return (j->status & 0xFF);
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
