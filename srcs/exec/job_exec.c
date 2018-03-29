/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:12:24 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/29 12:55:26 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
**	errno is only used to prevent race condition.
*/

#include <errno.h>

static int				print_err(char *msg)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	return (1);
}

size_t					ft_read(int fd, char *buffer, size_t size)
{
	size_t				ret;
	size_t				total;

	total = 0;
	while (size)
	{
		if ((ret = read(fd, buffer + total, size)) == (size_t)-1)
		{
			perror("read, ft_read, getpid");
			return ((size_t)-1);
		}
		total += ret;
		size -= ret;
	}
	return (0);
}

static void				lgetpid(t_job *j, int fd)
{
	t_proc				*p;
	int					pid;

	p = j->procs;
	while (p->next != NULL)
	{
		if (ft_read(fd, (char*)&pid, 4) == (size_t)-1)
		{
			dprintf(STDERR_FILENO, "Could not get pipe pids\n");
			return ;
		}
		p->pid = pid;
		p = p->next;
	}
}

int						job_pipe(t_job *j, t_ctx *ctx)
{
	pid_t				pid;
	int					ret;
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
	{
		j->pgid = pid;
		if ((ret = setpgid(pid, pid)) != 0 && errno != ESRCH)
			perror("job_pipe setpgid");
		t_proc *p = j->procs;
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
	else
	{
		j->pgid = getpid();
		if ((ret = setpgid(j->pgid, j->pgid)) != 0 && errno != ESRCH)
			perror("job_pipe setpgid");
		close(mypipe[0]);
		exec_pipe(j, ctx, mypipe[1]);
		close(mypipe[1]);
	}
	return (0);
}

static int				fork_do(t_job *j, t_proc *p, t_ctx *ctx)
{
	pid_t				pid;
	int					ret;

	if ((pid = fork()) < 0)
		return (print_err("21sh: fork: could not fork\n"));
	else if (pid == 0)
		proc_exec(p, j, ctx);
	else
	{
		p->pid = pid;
		j->pgid = pid;
		if ((ret = setpgid(pid, pid)) != 0 && errno != ESRCH)
			perror("setpgid job one fork_do");
	}
	return (0);
}

static int				job_one(t_job *j, t_ctx *ctx)
{
	t_proc				*p;

	p = j->procs;
	if (p->asmts != NULL && p->argv[0] == NULL && j->bg == 0)
		prefork_assign(ctx, p->asmts);
	else if (p->argv[0] != NULL)
		prepare_fork(p, ctx, 0);
	if (fork_do(j, p, ctx) == 1)
		return (1);
	return (0);
}

int						job_exec(t_job *j, t_ctx *ctx)
{
	int					exp_err;

	if (j == NULL)
		return (0);
	if (j->parent == j)
		j->command = get_command(j);
	j->status = expand_job(j, ctx, &exp_err);
	if (exp_err == 0 && (j->procs->next != NULL ? job_pipe(j, ctx) == 1
							: job_one(j, ctx) == 1))
		return (1);
	if (j->parent->bg == 0 && exp_err)
		return (job_donext(j, ctx));
	else if (j->parent->bg == 0)
		return (job_next(j, ctx));
	return (0);
}
