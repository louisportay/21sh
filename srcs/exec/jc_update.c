/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 10:56:09 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/27 17:02:19 by vbastion         ###   ########.fr       */
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
	}
	else if (WIFSIGNALED(status))
	{
		p->completed = 1;
		dprintf(STDERR_FILENO, "%d: Terminated by signal %d.\n", (int)p->pid, 
				WTERMSIG(status));
		j->parent->completed = JC_SIGNAL;
	}
}

void					jc_updatejob(t_job *j)
{
	j = j->parent;
	j->done = jc_status(j) == JC_DONE;
}

void					jc_updatepipe(t_job *j)
{
	t_proc				*p;

	p = j->procs;
	while (p != NULL)
	{
		if (p->completed == 0)
			return ;
		p = p->next;
	}
	j->completed = 1;
}

void					jc_update(t_job *j, pid_t pid, int status)
{
	t_proc				*p;

	p = j->procs;
	while (p != NULL)
	{
		if (p->pid == pid)
		{
			jc_updateproc(j, p, status);
			jc_updatepipe(j);
			jc_updatejob(j);
			break ;
		}
	}
}
