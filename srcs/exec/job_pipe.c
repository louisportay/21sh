/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 11:32:11 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/08 17:58:37 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int				lgetpid(t_job *j, int fd)
{
	t_proc				*p;
	int					pid;
	int					err;

	p = j->procs;
	err = 0;
	while (p->next != NULL)
	{
		if (ft_read(fd, (char*)&pid, sizeof(int)) == (size_t)-1)
		{
			ft_dprintf(STDERR_FILENO, "Could not get pipe pids\n");
			return (1);
		}
		else if (pid == -1)
			err = 1;
		p->pid = pid;
		p = p->next;
	}
	return (err);
}

static int				l_job_pipe(t_job *j, pid_t pid, int mypipe[2])
{
	t_proc				*p;
	int					ret;

	p = j->procs;
	while (p != NULL)
	{
		if (p->next == NULL)
			p->pid = pid;
		p = p->next;
	}
	close(mypipe[1]);
	ret = lgetpid(j, mypipe[0]);
	close(mypipe[0]);
	if (ret)
		j->procs->pid = pid;
	return (ret);
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
		return (l_job_pipe(j, pid, mypipe) ? -1 : 0);
	else
	{
		close(mypipe[0]);
		exec_pipe(j, ctx, mypipe[1]);
		close(mypipe[1]);
	}
	return (0);
}
