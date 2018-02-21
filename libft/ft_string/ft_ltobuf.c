/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 13:56:23 by vbastion          #+#    #+#             */
/*   Updated: 2017/11/11 20:42:19 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

double			rounder(int p)
{
	double		d;

	d = 5.;
	while (p > 0)
	{
		d /= 10;
		p--;
	}
	return (d);
}

static size_t	get_len(intmax_t l, size_t base)
{
	size_t		len;

	len = 0;
	if (l == 0)
		return (1);
	while (l != 0)
	{
		len++;
		if ((l * -1 > -1))
			l *= -1;
		l /= base;
	}
	return (len);
}

static size_t	get_ull_len(uintmax_t ull, size_t base)
{
	size_t		len;

	len = 0;
	if (ull == 0)
		return (1);
	while (ull != 0)
	{
		len++;
		ull /= base;
	}
	return (len);
}

void			ft_ltobuf(long long l, size_t base, u_char upper, char *buf)
{
	size_t		pos;
	size_t		len;
	char		tmp;
	u_char		sign;

	len = get_len(l, base);
	pos = 0;
	sign = l < 0;
	if (l == 0)
	{
		ft_strncpy(buf, "0", 1);
		return ;
	}
	sign && (buf[0] = '-');
	while (l != 0)
	{
		if ((l * -1) > -1)
			l *= -1;
		tmp = (l % base);
		buf[len - pos - (sign ? 0 : 1)] = tmp > 9 ? 'a' + tmp - 10 : '0' + tmp;
		if (tmp > 9 && upper == 1)
			buf[len - pos - 1] -= 32;
		pos++;
		l /= base;
	}
}

void			ft_ultobuf(unsigned long long l, size_t base, u_char upper,
							char *buf)
{
	size_t		pos;
	u_char		tmp;
	size_t		len;

	len = get_ull_len(l, base);
	pos = 0;
	if (l == 0)
	{
		ft_strncpy(buf, "0", 1);
		return ;
	}
	while (l != 0)
	{
		tmp = l % base;
		buf[len - pos - 1] = tmp > 9 ? 'a' + tmp - 10 : '0' + tmp;
		if (tmp > 9 && upper == 1)
			buf[len - pos - 1] -= 32;
		pos++;
		l /= base;
	}
}
