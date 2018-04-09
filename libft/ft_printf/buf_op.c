/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 17:36:50 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/09 11:44:15 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	qbuf_addn(buf->buf, (char *)str, n);
	return (n);
}
