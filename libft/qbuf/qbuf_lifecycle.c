/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qbuf_lifecycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 19:19:30 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/10 12:10:03 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "qbuf.h"

t_qbuf				*qbuf_new(size_t first)
{
	t_qbuf			*buf;

	if ((buf = (t_qbuf *)ft_memalloc(sizeof(t_qbuf))) == NULL)
		return (NULL);
	if ((buf->buffer = ft_strnew(first)) == NULL)
	{
		ft_memdel((void **)&buf);
		return (NULL);
	}
	buf->size = first;
	return (buf);
}

char				*qbuf_del(t_qbuf **buf)
{
	char			*str;

	if (buf == NULL || *buf == NULL)
		return (NULL);
	str = ft_strndup((*buf)->buffer, (*buf)->used);
	ft_strdel(&((*buf)->buffer));
	ft_memdel((void **)buf);
	return (str);
}

void				qbuf_clear(t_qbuf *buf)
{
	ft_bzero(buf->buffer, buf->used);
	buf->used = 0;
}

void				qbuf_nuke(t_qbuf **buf)
{
	ft_strdel(&((*buf)->buffer));
	ft_memdel((void **)buf);
}
