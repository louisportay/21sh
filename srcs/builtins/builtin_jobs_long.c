/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs_long.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:44:22 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/28 18:52:37 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char				*lproc_cmd(t_proc *p)
{
	t_qbuf				*buf;
	t_asmt				*a;
	size_t				i;
	
	buf = qbuf_new(1 << 8);
	a = p->asmts;
	while (a != NULL)
	{
		qbuf_add(buf, a->key);
		qbuf_addc(buf, '=');
		qbuf_add(buf, a->value);
		qbuf_addc(buf, ' ');
		a = a->next;
	}
	i = 0;
	while (p->argv[i] != NULL)
	{
		qbuf_add(buf, p->argv[i]);
		qbuf_addc(buf, ' ');
		i++;
	}
	return (qbuf_del(&buf));
}

static char				*lgetstatus(t_job *j)
{
	static char			buf[24];

	ft_bzero(buf, 24);
	if (j->parent->status & JOB_DON)
	{
		if (j->parent->status & 0xFF)
			return ("Done");
		else
		{
			ft_snprintf(buf, 24, "Exit %d", j->parent->status & 0xFF);
			return (buf);
		}
	}
	else if (j->status & JOB_SIG)
	{
		ft_snprintf(buf, 24, "Terminated: %d", j->status & 0xFF);
		return (buf);
	}
	else if (j->status & JOB_STP)
		return ("Stopped");
	else
		return ("Running");
}

static void				ljob_print(t_ctx *ctx, size_t i, int flag)
{
	t_proc				*p;
	t_job				*j;
	char				*cmd;

	j = ctx->bg_jobs[i];
	if (((BU_J_S & flag) && (j->status & JOB_STP) == 0)
		|| ((BU_J_R & flag) && (j->status & JOB_STP)))
		return ;
	p = j->procs;
	cmd = lproc_cmd(p);
	ft_printf("[%zu]%c  %-5d %-24s%s\n", i + 1, jc_getstatus(j), p->pid,
				lgetstatus(j), cmd);
	ft_strdel(&cmd);
	while (p->next != NULL)
	{
		{	/*	DO INTERMEDIARY JOBS	*/	}
		p = p->next;
	}
	if (p != NULL)
		ft_printf("%5s%-5d%25s | %s &\n", " ", p->pid, " ", lproc_cmd(p));
}

void					bu_jobs_long(t_ctx *ctx, int flag)
{
	size_t				i;
	t_job				*j;

	i = 0;
	while (i < ctx->bg_cnt)
	{
		if ((j = ctx->bg_jobs[i]) != NULL)
			ljob_print(ctx, i, flag);
		i++;
	}
}
