/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 08:56:06 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/27 11:41:13 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

#define JC_NUL -1
#define JC_STP 0
#define JC_RUN 1
#define JC_TODO 2

int						jc_getnext(t_job *j, t_job **next, int *status)
{
//	if (j == NULL)
//		return (-1);
//	if (j->stopped)
//		return (JC_STP);
//	else if (j->stopped == 0 && j->completed == 0)
//	{
//		if (j->running)
//			return (JC_RUN);
//		*next = j;
//		return (JC_TODO);
//	}
//	else if (j->completed)
//	{
//		if (j->status == 0 && j->err != NULL)
//		{
//			ret = jc_getnext(j->ok, next, status);
//			if (ret == JC_RUN || ret == JC_TODO)
//				return (ret);
//			else if (*status == 0)
//				return (JC_STP);
//			else if (*status != 0)
//				return (jc_getnext(j->err, next, status));
//
//		}
//		else if (j->status == 0)
//			return (jc_getnext(j->err, next, status));
//	}
//	dprintf(STDERR_FILENO, "Could not retrieve data for job(%d)\n", j->pgid);
	(void)j;
	(void)next;
	(void)status;
	return (JC_NUL);
}

void					jc_signal(int signo)
{
	pid_t				pid;
	int					status;
	t_job				*parent;
	t_job				*j;
	t_ctx				*ctx;

	if (signo != SIGCHLD)
		return ;
	ctx = get_ctxaddr(NULL);
	while ((pid = waitpid(WAIT_ANY, &status, WUNTRACED)) > 0)
	{
		if ((parent = jc_getparent(ctx, pid, &j)) == NULL)
			dprintf(STDERR_FILENO, "No job saved for (%d)\n", pid);
		jc_update(j, parent, pid, status);
	}
}
