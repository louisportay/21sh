/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 13:46:09 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/24 17:55:33 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

int						job_isstopped(t_job *job)
{
	t_proc				*p;

	p = job->first_process;
	while (p != NULL)
	{
		if (p->completed == 0 && p->stopped == 0)
			return (0);
		p = p->next;
	}
	return (1);
}

int						job_iscompleted(t_job *job)
{
	t_proc				*p;

	p = job->first_process;
	while (p != NULL)
	{
		if (p->completed == 0)
			return (0);
		p = p->next;
	}
	return (1);
}
