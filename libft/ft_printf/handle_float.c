/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 14:34:19 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/25 18:09:46 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			handle_flo_pre(char *buf, size_t *len, t_flag *flag,
									double f)
{
	size_t		pre;
	int			tmp_i;

	buf[(*len)] = '.';
	(*len)++;
	pre = (flag->sz_flag & 6) ? flag->pre : 6;
	f += rounder(pre + 1);
	while (pre != 0)
	{
		if (f == 0)
		{
			buf[(*len)++] = '0';
			pre--;
			continue ;
		}
		f *= 10;
		tmp_i = (int)(f);
		f -= tmp_i;
		pre--;
		buf[(*len)] = '0' + tmp_i;
		(*len)++;
	}
	return (1);
}

static int			print_float(char *buf, size_t len, t_flag *flag)
{
	u_char			spec;

	spec = (((flag->flag & (1 << 10)) == 0)
			| (((flag->sz_flag & 1) && flag->min > len) << 1));
	if (spec == 3)
		fpf_buf_addfillers((flag->flag & (1 << 9)) == 0, flag->min - len);
	fpf_buf_add(buf, len);
	if (spec == 2)
		fpf_buf_addfillers(1, flag->min - len);
	return (1);
}

int					fpf_handle_flo(va_list *ap, t_flag *flag)
{
	char		*buf;
	long long	real;
	double		f;
	size_t		len;
	u_char		neg;

	buf = fpf_buf_get()->tmp_buf;
	ft_bzero(buf, FT_TMPBSZ);
	f = va_arg(*ap, double);
	neg = f < 0;
	if (neg)
	{
		f = -f;
		buf[0] = '-';
	}
	len = neg;
	real = (long long)f;
	ft_ltobuf(real, 10, 0, buf + len);
	len = fpf_strlen(buf);
	f -= real;
	if (((flag->sz_flag & 6) && flag->pre != 0) || ((flag->sz_flag & 6) == 0))
		handle_flo_pre(buf, &len, flag, f);
	return (print_float(buf, len, flag));
}
