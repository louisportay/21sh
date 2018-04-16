/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 15:20:05 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/09 12:22:58 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void			lset(t_ctx *ctx, t_qbuf *buf)
{
	qbuf_add(buf, BU_SET_MEXPO);
	qbuf_add(buf, ctx->set & BU_SET_EXPOR ? BU_SET_ON : BU_SET_OFF);
	qbuf_add(buf, BU_SET_BREXP);
	qbuf_add(buf, ctx->set & BRACE_EXPAND ? BU_SET_ON : BU_SET_OFF);
	qbuf_add(buf, BU_SET_MFNEX);
	qbuf_add(buf, ctx->set & BU_SET_FNEXP ? BU_SET_ON : BU_SET_OFF);
	qbuf_add(buf, BU_SET_MONCM);
	qbuf_add(buf, ctx->set & BU_SET_ONCMD ? BU_SET_ON : BU_SET_OFF);
	qbuf_add(buf, BU_SET_GLDOT);
	qbuf_add(buf, ctx->set & DOTGLOB ? BU_SET_ON : BU_SET_OFF);
	qbuf_add(buf, BU_SET_GLNUL);
	qbuf_add(buf, ctx->set & NULLGLOB ? BU_SET_ON : BU_SET_OFF);
	qbuf_add(buf, BU_SET_GLFAI);
	qbuf_add(buf, ctx->set & FAILGLOB ? BU_SET_ON : BU_SET_OFF);
}

static void			lcmd(t_ctx *ctx, t_qbuf *buf)
{
	qbuf_add(buf, "set ");
	qbuf_addc(buf, ctx->set & BU_SET_EXPOR ? '-' : '+');
	qbuf_add(buf, "a\nset ");
	qbuf_addc(buf, ctx->set & BRACE_EXPAND ? '-' : '+');
	qbuf_add(buf, "B\nset ");
	qbuf_addc(buf, ctx->set & BU_SET_FNEXP ? '-' : '+');
	qbuf_add(buf, "f\nset ");
	qbuf_addc(buf, ctx->set & BU_SET_ONCMD ? '-' : '+');
	qbuf_add(buf, "x\nset ");
	qbuf_addc(buf, ctx->set & DOTGLOB ? '-' : '+');
	qbuf_add(buf, "d\nset ");
	qbuf_addc(buf, ctx->set & NULLGLOB ? '-' : '+');
	qbuf_add(buf, "n\nset ");
	qbuf_addc(buf, ctx->set & FAILGLOB ? '-' : '+');
	qbuf_add(buf, "F\n");
}

static void			lloc(t_ctx *ctx, t_qbuf *buf)
{
	int				i;

	i = 0;
	while (ctx->locals[i] != NULL)
	{
		qbuf_add(buf, ctx->locals[i]);
		qbuf_addc(buf, '\n');
		i++;
	}
}

static void			lvar(t_ctx *ctx, t_qbuf *buf)
{
	int				i;

	i = 0;
	while (ctx->environ[i] != NULL)
	{
		qbuf_add(buf, ctx->environ[i]);
		qbuf_addc(buf, '\n');
		i++;
	}
	lloc(ctx, buf);
}

int					ft_set(t_proc *p, t_ctx *ctx)
{
	int				opt;
	t_qbuf			*buf;

	p->type = BUILTIN;
	if (p->argv[1] == NULL)
	{
		buf = qbuf_new(1 << 8);
		lvar(ctx, buf);
		qbuf_printclose(&buf, STDOUT_FILENO);
		return (0);
	}
	if ((opt = bu_set_getopts(p, ctx, 1)) == -1)
		return (1);
	buf = opt != 0 ? qbuf_new(1 << 8) : NULL;
	if (opt & BU_SET_PRLOC)
		lloc(ctx, buf);
	if (opt & BU_SET_PRVAR)
		lvar(ctx, buf);
	if (opt & BU_SET_PRSET)
		lset(ctx, buf);
	if (opt & BU_SET_PRCMD)
		lcmd(ctx, buf);
	if (opt != 0)
		qbuf_printclose(&buf, STDOUT_FILENO);
	return (0);
}
