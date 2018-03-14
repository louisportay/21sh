/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 13:10:43 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/14 13:54:28 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char					jc_getstatus(t_job *j)
{
	t_ctx				*ctx;

	ctx = get_ctxaddr(NULL);
	if (ctx->bgs != NULL && (t_job *)ctx->bgs->content == j)
		return ('+');
	else if (ctx->bgs->next != NULL
				&& (t_job *)ctx->bgs->next->content == j)
		return ('-');
	else
		return (' ');
}
/*	
**	void					jc_notify(t_job *j, t_ctx *ctx, int i, int all)
**	{
**		if (all && j->parent->status & JOB_SIG)
**		{
**			printf("[%d]%-3c%-12s: %-12d%s\n", i + 1, jc_getstatus(j), "Terminated",
**					j->parent->status & 0xFF, j->parent->command);
**		}
**		else if (all && (j->status & JOB_STP))
**		{
**			printf("[%d]%-3c%-24s%s\n", i + 1, jc_getstatus(j), "Stopped",
**					j->parent->command);
**		}
**		else if (j->parent->status & JOB_DON)
**		if (j->parent->status & (JOB_DON))
**		{
**			if (j->parent->status == 0)
**				printf("[%d]%-3c%-24s%s\n", i + 1, jc_getstatus(j), "Done",
**						j->parent->command);
**			else
**				printf("[%d]%-3c%s %-3d%16c%s\n", i + 1, jc_getstatus(j), "Exit",
**						j->parent->status, jc_getstatus(j), j->parent->command);
**			jc_rmbg(ctx, j);
**		}
**		else if (all && j->stopped)
**			printf("[%d]%-3c%-24s%s\n", i + 1, jc_getstatus(j), "Stopped",
**					j->parent->command);
**		else if (all)
**			printf("[%d]%-3c%-24s%s\n", i + 1, jc_getstatus(j), "Running",
**					j->parent->command);
**	}
**	
**	void					jc_print(t_ctx *ctx, int all, int verbose)
**	{
**		size_t				i;
**	
**		i = 0;
**		while (i < ctx->bg_cnt)
**		{
**			if (ctx->bg_jobs[i] != NULL)
**				jc_notify(ctx->bg_jobs[i], ctx, (int)i, all);
**			i++;
**		}
**		if (verbose)
**		{
**			for (i = 0; i < ctx->bg_cnt; i++)
**			{
**				t_job *j = ctx->bg_jobs[i];
**				if (j == NULL)
**					continue ;
**				printf("[%zu]   %s (%d)\n", i + 1, j->parent->command, j->pgid);
**				for (t_proc *p = j->procs; p != NULL; p = p->next)
**				{
**					printf("\t");
**					for (size_t j = 0; p->argv[j] != NULL; j++)
**						printf("%s ", p->argv[j]);
**					printf("(%d)\n", p->pid);
**				}
**			}
**		}
**	}
*/

#define SBUF_SZ 32

static char				*lgetdone(int status)
{
	static char			tbuf[9];

	ft_bzero(tbuf, 9);
	snprintf(tbuf, 9, "Exit %d", status & 0xFF);
	return (tbuf);
}

static char				*lgetstatus(int r, int status)
{
	if (r & JOB_SIG)
		return ("Terminated");
	else if (r & JOB_STP)
		return ("Stopped");
	else if (r & JOB_DON)
		return (lgetdone(status));
	else
		return ("Running");
}

static char				*lgetcode(int r, t_job *j)
{
	static char			tbuf[12];

	if (r & JOB_SIG)
		snprintf(tbuf, 12, "%-12d", j->parent->status & 0xFF);
	else
		ft_bzero(tbuf, 12);
	return (tbuf);
}

void					jc_notify(t_job *j, t_ctx *ctx, int i, int all)
{
	int					r;
	char				sbuf[SBUF_SZ + 1];

	(void)ctx;
	if (j != NULL)
	{
		r = j->parent->status & (JOB_STP | JOB_SIG | JOB_DON);
		if (r == JOB_DON || all)
		{
			ft_bzero(sbuf, SBUF_SZ + 1);
			snprintf(sbuf, SBUF_SZ, "[%d]%-3c%-10s%c %-12s", (int)i + 1,
						jc_getstatus(j), lgetstatus(r, j->parent->status),
						(j->parent->status & JOB_SIG) ? ':' : ' ',
						lgetcode(r, j));
		}

	}
}

void					jc_print(t_ctx *ctx, int all, int verbose)
{
	int					flag;
	size_t				i;
//	t_qbuf				*buf;
	t_job				*j;

//	buf = qbuf_new(1 >> 8);
	flag = (all != 0) | ((verbose != 0) << 1);
	i = 0;
	while (i < ctx->bg_cnt)
	{
		j = ctx->bg_jobs[i];
		jc_notify(j, ctx, i, all);
		i++;
	}
}
