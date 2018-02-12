/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_chgstat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:13:57 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/12 15:20:22 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int				update_status(t_job *job, pid_t pid, int status)
{
	t_proc				*proc;

	while (job != NULL)
	{
		proc = job->procs;
		while (proc != NULL)
		{
			if (proc->pid == pid)
			{
				proc->status = status;
				if (WIFEXITED(status))
					proc->stopped = 1;
				else if (WIFSIGNALED(status))
				{
					proc->completed = 1;
					dprintf(STDERR_FILENO, "%s (%d) stopped by sig(%d)\n",
							proc->argv[0], pid, WTERMSIG(status));
				}
				return (0);
			}
			proc = proc->next;
		}
		job = job->next;
	}
	return (-1);
}

int						proc_chgstat(t_job *job, pid_t pid, int status)
{
	if (pid > 0)
		return (update_status(job, pid, status));
	else if (pid == 0)
		return (-1);
	else
	{
		dprintf(STDERR_FILENO, "Error in waitpid\n");
		return (-1);
	}
}
