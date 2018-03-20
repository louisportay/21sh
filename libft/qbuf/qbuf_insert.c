/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qbuf_insert.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 19:23:49 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/19 16:10:25 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "qbuf.h"

int					qbuf_addc(t_qbuf *buf, char c)
{
	if (buf->used + 1 == buf->size)
	{
		if (qbuf_grow(buf) == 0)
			return (0);
	}
	buf->buffer[buf->used] = c;
	buf->used++;
	return (1);
}

int					qbuf_add(t_qbuf *buf, char *str)
{
	if (str == NULL)
		return (0);
	return (qbuf_addn(buf, str, ft_strlen(str)));
}

int					qbuf_addl(t_qbuf *buf, long l)
{
	char			s[21];
	unsigned long	m;
	int				i;

	i = ft_lwidth(l);
	m = (l < 0) ? -l : l;
	s[i--] = '\0';
	s[i--] = (m % 10) + '0';
	while ((m /= 10) != 0)
		s[i--] = (m % 10) + '0';
	s[0] = (l < 0) ? '-' : s[0];
	return (qbuf_add(buf, s));
}

int					qbuf_addn(t_qbuf *buf, char *str, size_t n)
{
	size_t			total;

	if (buf == NULL || str == NULL || n == (size_t)-1)
		return (0);
	total = buf->used + n;
	if (total < buf->size)
	{
		ft_strncpy(buf->buffer + buf->used, str, n);
		buf->used = total;
		return (1);
	}
	if (qbuf_grown(buf, total * 2) == 0)
		return (0);
	ft_strncat(buf->buffer, str, n);
	buf->used = total;
	return (1);
}
