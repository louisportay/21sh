/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 11:32:11 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/31 11:32:29 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void				lgetpid(t_job *j, int fd)
{
	t_proc				*p;
	int					pid;

	p = j->procs;
	while (p->next != NULL)
	{
		if (ft_read(fd, (char*)&pid, 4) == (size_t)-1)
		{
			ft_dprintf(STDERR_FILENO, "Could not get pipe pids\n");
			return ;
		}
		p->pid = pid;
		p = p->next;
	}
}

static void				l_job_pipe(t_job *j, pid_t pid, int mypipe[2])
{
	t_proc				*p;

	p = j->procs;
	while (p != NULL)
	{
		if (p->next == NULL)
			p->pid = pid;
		p = p->next;
	}
	close(mypipe[1]);
	lgetpid(j, mypipe[0]);
	close(mypipe[0]);
}

int						job_pipe(t_job *j, t_ctx *ctx)
{
	pid_t				pid;
	int					mypipe[2];

	if (pipe(mypipe) == -1)
	{
		ft_dprintf(STDERR_FILENO, "Could not retrieve pids of the pipe\n");
		return (1);
	}
	if ((pid = fork()) < 0)
	{
		close(mypipe[0]);
		close(mypipe[1]);
		return (1);
	}
	else if (pid != 0)
		l_job_pipe(j, pid, mypipe);
	else
	{
		close(mypipe[0]);
		exec_pipe(j, ctx, mypipe[1]);
		close(mypipe[1]);
	}
	return (0);
}
