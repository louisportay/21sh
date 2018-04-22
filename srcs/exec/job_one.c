/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_one.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/31 11:37:17 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/22 20:16:09 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int				lfork_do(t_job *j, t_proc *p)
{
	pid_t				pid;

	if ((pid = fork()) < 0)
	{
		ft_putstr_fd("42sh: fork: could not fork\n", STDERR_FILENO);
		return (1);
	}
	else if (pid == 0)
		proc_exec(p);
	else
	{
		if (job_setpgid(pid, pid) == -1)
			return (1);
		else if (job_setpgrp(pid) == -1)
			return (1);
		p->pid = pid;
		j->pgid = pid;
	}
	return (0);
}

int						restore_fds(t_ctx *ctx)
{
	dup2(ctx->std_fd[0], STDIN_FILENO);
	dup2(ctx->std_fd[1], STDOUT_FILENO);
	dup2(ctx->std_fd[2], STDERR_FILENO);
	return (1);
}

static void				set_proc_status(t_job *j, t_proc *p)
{
	if (p->is_err == 0)
		exec_print_err(p->type, p->type == EXNFOD ? p->data.path : p->argv[0]);
	p->status |= ((p->type & (EXNFD | EXNFOD)) ? 127 : 1) | JOB_CMP;
	j->status = p->status;
}

int						job_one(t_job *j, t_ctx *ctx)
{
	t_proc				*p;
	int					ret;
	int					fd[7];

	ft_bzero(fd, sizeof(int) * 7);
	ret = 0;
	p = j->procs;
	if (ctx->set & BU_SET_ONCMD)
		proc_print(p);
	if (do_redir(p->redirs, fd) == -1)
		return (restore_fds(ctx));
	if (p->asmts != NULL
		&& p->argv[0] == NULL)
		prefork_assign(ctx, p->asmts);
	else if (p->argv[0] != NULL)
		prepare_fork(p, ctx, 0);
	if (p->type == BINARY && lfork_do(j, p) == 1)
		ret = 1;
	else if ((p->type & (EXDIR | EXPERM | EXNFD | EXNFOD)) != 0)
		set_proc_status(j, p);
	clear_lfd(fd);
	restore_fds(ctx);
	return (p->is_err ? 1 : ret);
}
