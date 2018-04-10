/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qbuf_grow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 12:08:56 by lportay           #+#    #+#             */
/*   Updated: 2018/04/10 12:09:30 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "qbuf.h"

int					qbuf_grow(t_qbuf *buf)
{
	return (qbuf_grown(buf, buf->size * 2));
}

int					qbuf_grown(t_qbuf *buf, size_t n)
{
	char			*str;

	if ((str = ft_strnew(n)) == NULL)
		return (0);
	buf->size = n;
	ft_strcpy(str, buf->buffer);
	ft_strdel(&buf->buffer);
	buf->buffer = str;
	return (1);
}
