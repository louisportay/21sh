/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:18:08 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/19 21:06:39 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int				ft_echo(t_proc *p, t_ctx *ctx)
{
	int			i;
	int			nl;
	t_qbuf		*buf;

	(void)ctx;
	p->type = BU_STR;
	if (p->argv[1] == NULL)
	{
		p->data.str = ft_strdup("1\n");
		return (0);
	}
	nl = (ft_strcmp("-n", p->argv[1]) != 0);
	i = (nl ? 0 : 1) + 1;
	buf = qbuf_new(1 << 8);
	qbuf_addc(buf, '1');
	while (p->argv[i] != NULL)
	{
		qbuf_add(buf, p->argv[i++]);
		if (p->argv[i] != NULL)
			qbuf_addc(buf, ' ');
	}
	if (nl)
		qbuf_addc(buf, '\n');
	p->data.str = qbuf_del(&buf);
	return (0);
}
