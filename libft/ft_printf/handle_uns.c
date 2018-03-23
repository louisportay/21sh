/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_uns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 14:34:11 by vbastion          #+#    #+#             */
/*   Updated: 2017/08/08 13:05:47 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int						fpf_get_base(t_flag *flag)
{
	if (fpf_strchr("oO", flag->c) != NULL)
		return (8);
	else if (fpf_strchr("pxX", flag->c) != NULL)
		return (16);
	else
		return (10);
}

int						fpf_handle_bun(va_list *ap, t_flag *flag)
{
	uintmax_t			u;
	char				*buf;

	buf = fpf_buf_get()->tmp_buf;
	if ((flag->flag & 12) != 0)
		u = va_arg(*ap, unsigned long long);
	else
		u = va_arg(*ap, u_long);
	fpf_bzero(buf, 30);
	fpf_ultobuf((uintmax_t)u, fpf_get_base(flag), 0, buf);
	fpf_strwithsize(buf, flag);
	return (1);
}

int						fpf_handle_uns(va_list *ap, t_flag *flag)
{
	unsigned long long	u;
	char				*buf;

	buf = fpf_buf_get()->tmp_buf;
	fpf_bzero(buf, 30);
	if ((flag->flag & 0xFF) == 32)
		u = (unsigned long long)va_arg(*ap, size_t);
	else if ((flag->flag & 0xFF) == 16)
		u = (unsigned long long)va_arg(*ap, uintmax_t);
	else if ((flag->flag & 0xFF) == 8)
		u = (unsigned long long)va_arg(*ap, u_long);
	else if ((flag->flag & 0xFF) == 4)
		u = va_arg(*ap, unsigned long long);
	else if ((flag->flag & 0xFF) == 2)
		u = (unsigned long long)(u_short)va_arg(*ap, u_int);
	else if ((flag->flag & 0xFF) == 1)
		u = (unsigned long long)(u_char)va_arg(*ap, u_int);
	else
		u = va_arg(*ap, u_int);
	fpf_ultobuf(u, fpf_get_base(flag), flag->c == 'X', buf);
	fpf_strwithsize(buf, flag);
	return (1);
}
