/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_exec_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 20:48:08 by lportay           #+#    #+#             */
/*   Updated: 2018/04/21 19:13:57 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"
#include <errno.h>

static int				l_get_exit_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status) | JOB_CMP);
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128 | JOB_CMP);
	else
		PRINT_TTY("UNHANDLED STATUS: %d\n", status);
	return (-1);
}

static void				l_wait_for_job(t_job *j)
{
	pid_t				pid;
	int					status;

	PRINT_TTY("Waiting for pgid: %d\n", j->pgid);
	while ((pid = waitpid(j->pgid, &status, 0)) != -1)
	{
		PRINT_TTY("\033[31mNotified about %d with status: %d\033[0m\n",
					pid, l_get_exit_code(status) & 0xFF);
		if (pid == j->pgid)
			j->status = l_get_exit_code(status) & 0xFF;
	}
	if (pid == -1 && errno != ECHILD)
	{
		if (errno == EINTR)
			ft_putstr_fd("42sh: waitpid: interrupted by a caught signal\n",
							STDERR_FILENO);
		else
			ft_putstr_fd("42sh: waitpid: context error\n", STDERR_FILENO);
		j->status = (-42 & 0xFF);
	}
	j->status = JOB_CMP | (j->status & 0xFF);
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
