/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_one.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 11:37:17 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/31 11:37:39 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int				fork_do(t_proc *p)
{
	pid_t				pid;

	if ((pid = fork()) < 0)
	{
		ft_putstr_fd("21sh: fork: could not fork\n", STDERR_FILENO);
		return (1);
	}
	else if (pid == 0)
		proc_exec(p);
	else
		p->pid = pid;
	return (0);
}

int						job_one(t_job *j, t_ctx *ctx)
{
	t_proc				*p;

	p = j->procs;
	if (p->asmts != NULL && p->argv[0] == NULL)
		prefork_assign(ctx, p->asmts);
	else if (p->argv[0] != NULL)
		prepare_fork(p, ctx, 0);
	if (fork_do(p) == 1)
		return (1);
	return (0);
}
