/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 13:07:02 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/25 18:08:52 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				fpf_handle_bde(va_list *ap, t_flag *flag)
{
	char		*buf;
	long		l;

	buf = fpf_buf_get()->tmp_buf;
	ft_bzero(buf, 23);
	l = va_arg(*ap, long);
	ft_ltobuf((long long)l, fpf_get_base(flag), 0, buf);
	fpf_strwithsize(buf, flag);
	return (1);
}

int				fpf_handle_dec(va_list *ap, t_flag *flag)
{
	char		*buf;
	long long	i;

	buf = fpf_buf_get()->tmp_buf;
	ft_bzero(buf, 23);
	if ((flag->flag & 0xFF) == 32)
		i = (long long)va_arg(*ap, size_t);
	else if ((flag->flag & 0xFF) == 16)
		i = (long long)va_arg(*ap, intmax_t);
	else if ((flag->flag & 0xFF) == 4)
		i = (long long)va_arg(*ap, long long);
	else if ((flag->flag & 0xFF) == 8)
		i = (long long)va_arg(*ap, long);
	else if ((flag->flag & 0xFF) == 2)
		i = (long long)(short)va_arg(*ap, int);
	else if ((flag->flag & 0xFF) == 1)
		i = (long long)(char)va_arg(*ap, int);
	else
		i = va_arg(*ap, int);
	ft_ltobuf(i, fpf_get_base(flag), 0, buf);
	fpf_strwithsize(buf, flag);
	return (1);
}
