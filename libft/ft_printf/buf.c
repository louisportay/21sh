/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 17:36:16 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/10 12:57:38 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_buf				*fpf_buf_get(void)
{
	static t_buf	buf = (t_buf){.init = 0};
//	if (buf.init == 0)
//	{
//		if (buf.type != FPF_S)
//		{
//			printf("Allocation qbuf_new\n");
//			buf.buf = qbuf_new(1 << 8);
//			printf("qbuf_new: %p\n", buf.buf);
//		}
//		buf.init = 1;
//	}
	return (&buf);
}

void				fpf_buf_init(t_buf *buf)
{
	if (buf == NULL)
		buf = fpf_buf_get();
	if (buf->type != FPF_S)
		buf->buf = qbuf_new(1 << 8);
	buf->init = 1;
}

int					fpf_buf_clear(t_buf *buf)
{
	char			*str;

	if (buf == NULL)
		buf = fpf_buf_get();
	if (buf->type == FPF_S)
	{
		buf->init = 0;
		return (1);
	}
	else if (buf->type == FPF_A)
	{
		str = ft_strndup(buf->buf->buffer, buf->buf->used > buf->len ?
											buf->len : buf->buf->used);
		*(buf->out.out) = str;
	}
	else
		write(buf->out.fd, buf->buf->buffer, buf->buf->used);
	ft_strdel(&buf->buf->buffer);
	ft_memdel((void **)&buf->buf);
	return (1);
}

size_t				fpf_buf_gettotal(t_buf *buf)
{
	if (buf == NULL)
		buf = fpf_buf_get();
	return (buf->buf->used);
}
