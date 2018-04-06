/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 11:27:18 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/06 20:56:12 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				proc_foreach(t_proc *p, void (*act)(t_proc *))
{
	while (p != NULL)
	{
		act(p);
		p = p->next;
	}
}

void				proc_foreach_data(t_proc *p, void (*act)(t_proc *, void *),
										void *data)
{
	while (p != NULL)
	{
		act(p, data);
		p = p->next;
	}
}

static void			l_add_argv_to_buf(t_proc *p, t_qbuf *buf)
{
	size_t			i;

	qbuf_add(buf, "+ ");
	i = 0;
	while (p->argv[i] != NULL)
	{
		qbuf_add(buf, p->argv[i]);
		i++;
		qbuf_addc(buf, p->argv[i] != NULL ? ' ' : '\n');
	}
}

void				proc_print(t_proc *p)
{
	t_qbuf			*buf;
	t_asmt			*a;
	char			*str;

	buf = qbuf_new(1 << 8);
	a = p->asmts;
	while (a != NULL)
	{
		qbuf_add(buf, "+ ");
		qbuf_add(buf, a->key);
		qbuf_addc(buf, '=');
		qbuf_add(buf, a->value);
		qbuf_addc(buf, '\n');
		a = a->next;
	}
	if (p->argv[0] != NULL)
		l_add_argv_to_buf(p, buf);
	str = qbuf_del(&buf);
	ft_putstr_fd(str, STDIN_FILENO);
	ft_strdel(&str);
}
