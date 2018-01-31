/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtok_dollarpid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 10:55:00 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/14 18:12:57 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

void				vtok_addpid(t_membuf *buf, int clear)
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
		ft_mb_add(buf, r, len);
	else
	{
		ft_bzero(b, 32);
		pid = getppid();
		ft_ltobuf((long long)pid, 10, 0, b);
		r = ft_strdup(b);
		len = ft_strlen(b);
		ft_mb_add(buf, r, len);
	}
}

void				vtok_dolldoll(t_lvar *lvar)
{
	vtok_addpid(&lvar->buf, 0);
	lvar->curr_tok = lvar->curr_tok->next->next;
	lvar->next = &vtok_start;
}
