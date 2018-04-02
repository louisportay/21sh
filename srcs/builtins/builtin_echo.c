/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:18:08 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/02 16:14:00 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int				ft_echo(t_proc *p, t_ctx *ctx)
{
	int			i;
	int			nl;
	t_qbuf		*buf;

	(void)ctx;
	p->type = BUILTIN;
	if (p->argv[1] == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	nl = (ft_strcmp("-n", p->argv[1]) != 0);
	i = (nl ? 0 : 1) + 1;
	buf = qbuf_new(1 << 8);
	while (p->argv[i] != NULL)
	{
		qbuf_add(buf, p->argv[i++]);
		if (p->argv[i] != NULL)
			qbuf_addc(buf, ' ');
	}
	if (nl)
		qbuf_addc(buf, '\n');
	qbuf_printclose(&buf, STDOUT_FILENO);
	return (0);
}
