/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 17:19:50 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/21 12:00:18 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_vprintf(const char *format, va_list ap)
{
	t_buf		*buf;

	buf = fpf_buf_get();
	buf->type = FPF_FD;
	buf->out.fd = 1;
	return (fpf_worker(format, ap));
}

int				ft_vdprintf(int fd, const char *format, va_list ap)
{
	t_buf		*buf;

	if (fd == -1)
		return (-1);
	buf = fpf_buf_get();
	buf->type = FPF_FD;
	buf->out.fd = fd;
	return (fpf_worker(format, ap));
}

int				ft_vsprintf(char *str, const char *format, va_list ap)
{
	t_buf		*buf;

	buf = fpf_buf_get();
	buf->type = FPF_S;
	buf->out.tar = str;
	buf->len = UINT_MAX;
	return (fpf_worker(format, ap));
}

int				ft_vsnprintf(char *str, size_t size, const char *format,
								va_list ap)
{
	t_buf		*buf;

	buf = fpf_buf_get();
	buf->type = FPF_S;
	buf->out.tar = str;
	buf->len = size;
	return (fpf_worker(format, ap));
}
