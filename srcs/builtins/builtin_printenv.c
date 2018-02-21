/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:03:14 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/19 21:07:12 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int		traverse(t_proc *p, t_ctx *ctx)
{
	t_list		*lsts[2];
	char		*str;
	char		*ret;
	int			err;
	int			i;

	err = 0;
	lsts[0] = NULL;
	i = 1;
	while (p->argv[i] != NULL)
	{
		if ((str = ft_astr_getval(ctx->environ, p->argv[i])) != NULL)
			asprintf(&ret, "1%s\n", str);
		else
		{
			err |= 1;
			asprintf(&ret, "221sh: printenv: '%s' not found\n", p->argv[i]);
		}
		ft_list_insert(lsts, lsts + 1, list_create(ret));
		i++;
	}
	p->data.out = lsts[0];
	return (err);
}

int				ft_printenv(t_proc *p, t_ctx *ctx)
{
	int			i;
	t_qbuf		*buf;

	p->type = BUILTIN;
	if (p->argv[1] == NULL)
	{
		p->type = BU_STR;
		i = 0;
		buf = qbuf_new(1 << 8);
		qbuf_addc(buf, '1');
		while (ctx->environ[i] != NULL)
		{
			qbuf_add(buf, ctx->environ[i]);
			qbuf_addc(buf, '\n');
			i++;
		}
		p->data.str = qbuf_del(&buf);
		return (0);
	}
	return (traverse(p, ctx));
}