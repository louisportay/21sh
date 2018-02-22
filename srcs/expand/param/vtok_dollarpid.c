/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtok_dollarpid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 10:55:00 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/22 13:42:34 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

void				vtok_addpid(t_qbuf *buf, int clear)
{
	char			b[32];
	static char		*r = NULL;
	static size_t	len = (size_t)-1;
	pid_t			pid;

	if (clear)
	{
		ft_strdel(&r);
		return ;
	}
	if (r != NULL)
		qbuf_addn(buf, r, len);
	else
	{
		ft_bzero(b, 32);
		pid = getppid();
		ft_ltobuf((long long)pid, 10, 0, b);
		r = ft_strdup(b);
		len = ft_strlen(b);
		qbuf_addn(buf, r, len);
	}
}

void				vtok_dolldoll(t_lvar *lvar)
{
	vtok_addpid(lvar->buf, 0);
	lvar->curr_tok = lvar->curr_tok->next->next;
	lvar->next = &vtok_start;
}
