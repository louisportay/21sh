/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 16:55:38 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/24 17:23:55 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void				get_curr(t_job *j, t_qbuf *buf)
{
	t_proc				*p;
	int					i;

	p = j->procs;
	while (p != NULL)
	{
		i = 0;
		while (p->argv[i] != NULL)
		{
			qbuf_add(buf, p->argv[i++]);
			if (p->argv[i] != NULL)
				qbuf_addc(buf, ' ');
		}
		p = p->next;
		if (p != NULL)
			qbuf_add(buf, " | ");
	}
}

char					*get_command(t_job *j)
{
	t_qbuf				*buf;
	char				*str;
	t_job				*ok;

	buf = qbuf_new(1 << 8);
	get_curr(j, buf);
	ok = j->ok;
	while (ok != NULL)
	{
		qbuf_add(buf, " && ");
		get_curr(ok, buf);
		ok = ok->ok;
	}
	if (j->err != NULL)
	{
		if (j->err->parent != j->parent)
			j->err->parent = j->parent;
		qbuf_add(buf, " || ");
		str = get_command(j->err);
		qbuf_add(buf, str);
		ft_strdel(&str);
	}
	return (qbuf_del(&buf));
}
