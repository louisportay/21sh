/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 08:56:06 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/27 17:24:24 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void					jc_signal(int signo)
{
	pid_t				pid;
	int					status;
	t_job				*j;
	t_ctx				*ctx;

	if (signo != SIGCHLD)
		return ;
	ctx = get_ctxaddr(NULL);
	while ((pid = waitpid(WAIT_ANY, &status, WUNTRACED)) > 0)
	{
        printf("Signaled %d\n", pid);
		if ((j = jc_getjob(ctx, pid)) == NULL)
			dprintf(STDERR_FILENO, "No job saved for (%d)\n", pid);
		else
			jc_update(j, pid, status);
	}
}

static int				jc_getokstatus(t_job *j)
{
	while (j != NULL)
	{
		if (j->status != 0)
			return (j->status);
		j = j->ok;
	}
	return (0);
}

int						jc_pipestatus(t_job *j)
{
	t_proc				*p;

	p = j->procs;
	while (p->next != NULL)
		p = p->next;
	return (p->status);
}

int						jc_getstatus(t_job *j)
{
	j = j->parent;
	if (j->done == 0)
		return (-1);
	if (j->status == 0)
	{
		if (jc_getokstatus(j->ok) != 0)
			return (jc_getstatus(j->err));
		return (0);
	}
	return (jc_getstatus(j->err));
}
