/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 17:36:50 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/21 12:08:54 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			fpf_buf_str(const char *str, size_t n)
{
	size_t			to_write;
	size_t			rem_space;
	t_buf			*buf;

	buf = fpf_buf_get();
	rem_space = buf->len - buf->ret - 1;
	if ((size_t)buf->ret >= (buf->len - 1) || buf->len == 0)
	{
		buf->ret += n;
		return (1);
	}
	else if (rem_space > 0)
	{
		to_write = (rem_space > n) ? n : rem_space;
		fpf_strncpy(buf->out.tar + buf->ret, str, to_write);
		buf->ret += n;
		return (1);
	}
	return (0);
}

int					fpf_buf_addc(const char c)
{
	t_buf			*buf;

	buf = fpf_buf_get();
	qbuf_addc(buf->buf, c);
	return (1);
}

int					fpf_buf_addfillers(int ws, size_t sz)
{
	t_buf			*buf;

	buf = fpf_buf_get();
	while (sz > BIG_WS_SZ)
	{
		qbuf_addn(buf->buf, ws ? BIG_WS : BIG_00, BIG_WS_SZ);
		sz -= BIG_WS_SZ;
	}
	qbuf_addn(buf->buf, ws ? BIG_WS : BIG_00, sz);
	return (1);
}

int					fpf_buf_add(const char *str, size_t n)
{
	t_buf			*buf;

	buf = fpf_buf_get();
	if (buf->type & FPF_S)
		return (fpf_buf_str(str, n));
	else
		qbuf_addn(buf->buf, (char *)str, n);
	buf->ret += n;
	return (n);
}
