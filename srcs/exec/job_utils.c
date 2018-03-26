/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 13:46:09 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/26 13:27:32 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_job					*job_find(pid_t pid, t_job *job_list)
{
	while (job_list != NULL)
	{
		if (job_list->pgid == pid)
			return (job_list);
		job_list = job_list->next;
	}
	return (NULL);
}

int						job_stopped(t_job *job)
{
	t_proc				*p;

	p = job->procs;
	while (p != NULL)
	{
		if ((p->status & (JOB_CMP | JOB_STP)) == 0)
			return (0);
		p = p->next;
	}
	return (1);
}

int						job_completed(t_job *job)
{
	t_proc				*p;

	p = job->procs;
	while (p != NULL)
	{
		if ((p->status & JOB_CMP) == 0)
			return (0);
		p = p->next;
	}
	return (1);
}

void					job_fmtinfo(t_job *job, char *status)
{
	ft_dprintf(STDERR_FILENO, "%d %s: %s\n", job->pgid, status, job->command);
}
