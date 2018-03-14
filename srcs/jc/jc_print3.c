/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 13:10:43 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/14 16:34:23 by vbastion         ###   ########.fr       */
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

void					jc_notify(t_ctx *ctx, size_t i, int opts, t_qbuf *buf)
{
	t_job				*j;
	char				sbuf[33];
	int					d;

//	if ((opts & 1) == 0 && (ctx->bg_jobs[i]->status & JOB_DON) == 0)
//		return ;
	printf("printing: %s\n", ctx->bg_jobs[i]->parent->command);
	if (buf == NULL)
	{
		opts |= (1 << 2);
		buf = qbuf_new(1 << 8);
	}
	j = ctx->bg_jobs[i];
	ft_bzero(sbuf, 32);
	d = snprintf(sbuf, 5, "[%zu]", i + 1);
	d += sprintf(sbuf + d, "%c  ", jc_getstatus(j));
	if (j->status & JOB_SIG)
	{
		sprintf(sbuf + d, "%-12s%-12d", "Terminated: ", j->status & 0xFF);
		printf("%s\n", sbuf);
	}
	else if (j->status & JOB_STP)
		sprintf(sbuf + d, "%-24s", "Stopped");
	else if ((j->status & JOB_DON) && (j->status & 0xFF))
		sprintf(sbuf + d, "Exit %-19d", j->status & 0xFF);
	else if ((j->status & JOB_DON) && (j->status & 0xFF) == 0)
		sprintf(sbuf + d, "%-24s", "Done");
	else
		sprintf(sbuf + d, "%-24s", "Running");
	qbuf_add(buf, sbuf);
	qbuf_add(buf, j->parent->command);
	qbuf_addc(buf, '\n');
	if (opts & (1 << 2))
	{
		write(STDOUT_FILENO, buf->buffer, buf->used);
		qbuf_del(&buf);
	}
}

char					*jc_print(t_ctx *ctx, int all, int verbose)
{
	t_qbuf				*buf;
	size_t				i;
	int					opt;

	buf = qbuf_new(1 << 8);
	opt = (all != 0) | ((verbose != 0) << 1);
	i = 0;
	while (i < ctx->bg_cnt)
	{
		if (ctx->bg_jobs[i] != NULL)
		{
			qbuf_add(buf, ctx->bg_jobs[i]->parent->command);
			qbuf_addc(buf, '\n');
			jc_notify(ctx, i, opt, buf);
		}
		i++;
	}
	return (qbuf_del(&buf));
}
