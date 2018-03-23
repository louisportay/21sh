/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 15:46:26 by vbastion          #+#    #+#             */
/*   Updated: 2017/08/26 12:32:31 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t			fpf_tobin(unsigned long long bin, size_t bytes,
									char *buf, t_flag *flag)
{
	int					bit_pos;
	int					buf_pos;
	int					prefix;

	bit_pos = bytes * 8 - 1;
	prefix = (flag->flag & (1 << 8)) != 0;
	buf_pos = prefix ? 2 : 0;
	if (prefix)
		fpf_strncpy(buf, flag->c == 'b' ? "0b" : "0B", 2);
	while (bit_pos > -1)
	{
		buf[buf_pos++] = ((bin & (1 << bit_pos)) != 0) + '0';
		if (prefix == 0 && ((bit_pos % 8) == 0))
		{
			buf[buf_pos] = (flag->c == 'b' ? ' ' : '-');
			buf_pos++;
		}
		bit_pos--;
	}
	return ((bytes * 8) + (prefix ? 2 : (bytes - 1)));
}

static void				fpf_bin_get_val(va_list *ap, t_flag *flag, size_t *sz,
										unsigned long long *bin)
{
	if ((flag->flag & 1))
	{
		(*bin) = (unsigned long long)(unsigned char)va_arg(*ap, unsigned int);
		(*sz) = sizeof(unsigned char);
	}
	else if ((flag->flag & 2))
	{
		(*bin) = (unsigned long long)(unsigned short)va_arg(*ap, unsigned int);
		(*sz) = sizeof(unsigned short);
	}
	else if ((flag->flag & 4))
	{
		(*bin) = (unsigned long long)va_arg(*ap, unsigned long long);
		(*sz) = sizeof(unsigned long long);
	}
	else if ((flag->flag & 8))
	{
		(*bin) = (unsigned long long)va_arg(*ap, unsigned long);
		(*sz) = sizeof(unsigned long);
	}
	else
	{
		(*bin) = (unsigned long long)va_arg(*ap, unsigned int);
		(*sz) = sizeof(unsigned int);
	}
}

int						fpf_handle_bin(va_list *ap, t_flag *flag)
{
	size_t				sz;
	unsigned long long	bin;
	char				*buf;
	size_t				len;
	size_t				to_write;

	buf = fpf_buf_get()->tmp_buf;
	fpf_bzero(buf, 75);
	fpf_bin_get_val((va_list *)ap, flag, &sz, &bin);
	len = fpf_tobin(bin, sz, buf, flag);
	if ((flag->sz_flag & 4) != 0)
	{
		to_write = flag->pre < len ? flag->pre : len;
		if ((flag->sz_flag & 1 && (flag->flag & (1 << 10)) == 0)
			&& flag->min > to_write)
			fpf_buf_addfillers(1, flag->min - to_write);
		fpf_buf_add(buf, to_write);
		return (1);
	}
	if ((flag->sz_flag & 1) && flag->min > len && (flag->flag & (1 << 10)) == 0)
		fpf_buf_addfillers(1, flag->min - len);
	fpf_buf_add(buf, len);
	if ((flag->sz_flag & 1) && flag->min > len && (flag->flag & (1 << 10)) != 0)
		fpf_buf_addfillers(1, flag->min - len);
	return (1);
}
