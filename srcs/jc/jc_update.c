/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 14:04:15 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/07 18:10:45 by vbastion         ###   ########.fr       */
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
		j->parent->status = WTERMSIG(status);
		dprintf(STDERR_FILENO, "%d: Terminated by signal %d.\n", (int)p->pid, 
				j->parent->status);
        j->parent->done = 1;
	}
}

int						jc_updatepipe(t_job *j)
{
	t_proc				*p;
	pid_t				pid;
	int					status;

	if (j == NULL)
		return (0);
	p = j->procs;
	j->completed = 1;
	while (p != NULL)
	{
		if (p->completed == 1)
			;
		else if ((pid = waitpid(p->pid, &status, WNOHANG)) > 0)
			jc_updateproc(j, p, status);
		else if (pid == -1)
			return (-1);
		j->completed &= p->completed;
		if (p->stopped)
		{
			j->stopped = 1;
			return (1);
		}
		j->status = (p->next == NULL && j->completed) ? p->status : 0;
		p = p->next;
	}
	return (j->status);
}
