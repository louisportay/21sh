/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_oct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:05:37 by lportay           #+#    #+#             */
/*   Updated: 2017/04/25 14:38:49 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_pointer(t_printf *l, int *i, int j)
{
	l->s = ft_itoa_base_u(l->lg[j], 16);
	i[8] -= (l->lg[j] == 0) ? 0 : ft_strlen(l->s);
	i[2] -= 2 + ((i[8] > 0) ? i[8] : 0);
	i[2] -= (i[0] == 1 && i[8] == 0 && l->lg[j] == 0) ? 0 : ft_strlen(l->s);
	i[1] = (i[0] == 1) ? 0 : i[1];
	if (i[5] == 0 && i[1] == 0)
		putnc_in_buf(i[2], ' ', l->buf, &l->j);
	ft_strlower(l->s);
	puts_in_buf("0x", l->buf, &l->j);
	if (i[5] == 0 && i[1] == 1)
		putnc_in_buf(i[2], '0', l->buf, &l->j);
	putnc_in_buf((l->lg[j] == 0) ? i[8] - (int)ft_strlen(l->s) : i[8], '0',
			l->buf, &l->j);
	if (!(i[0] == 1 && l->lg[j] == 0 && i[8] == 0))
		puts_in_buf(l->s, l->buf, &l->j);
	ft_strdel(&l->s);
	if (i[5] == 1)
		putnc_in_buf(i[2], ' ', l->buf, &l->j);
}

static void	width_prec_x(t_printf *l, int *i, int j)
{
	if (i[7] == 0)
		l->s = ft_itoa_base((unsigned int)l->lg[j], 16);
	else if (i[7] == 1)
		l->s = ft_itoa_base((unsigned short)l->lg[j], 16);
	else if (i[7] == 2)
		l->s = ft_itoa_base((unsigned char)l->lg[j], 16);
	else if (i[7] == 3)
		l->s = ft_itoa_base_u((unsigned long)l->lg[j], 16);
	else if (i[7] == 4)
		l->s = ft_itoa_base_u((unsigned long long)l->lg[j], 16);
	else if (i[7] == 5)
		l->s = ft_itoa_base_u((unsigned long)l->lg[j], 16);
	else if (i[7] == 6)
		l->s = ft_itoa_base_u((size_t)l->lg[j], 16);
}

void		print_hexa(t_printf *l, int *i, int j)
{
	width_prec_x(l, i, j);
	if (i[9] == 'x')
		ft_strlower(l->s);
	i[1] = (i[0] == 1) ? 0 : i[1];
	i[8] -= (l->lg[j] != 0) ? ft_strlen(l->s) : 0;
	i[8] = (i[8] < 0) ? 0 : i[8];
	i[2] -= (i[8] + ft_strlen(l->s) + ((i[3] == 1) ? 2 : 0));
	i[2] += ((i[3] == 1) && l->lg[j] == 0) ? 2 : 0;
	i[2] += ((i[0] == 1) && l->lg[j] == 0) ? 1 : 0;
	if (i[5] == 0 && i[1] == 0)
		putnc_in_buf(i[2], ' ', l->buf, &l->j);
	if (i[3] == 1 && l->lg[j] != 0)
		puts_in_buf((i[9] == 'x') ? "0x" : "0X", l->buf, &l->j);
	if (i[5] == 0 && i[1] == 1)
		putnc_in_buf(i[2], '0', l->buf, &l->j);
	putnc_in_buf(i[8], '0', l->buf, &l->j);
	if (i[0] != 1 || l->lg[j] != 0)
		puts_in_buf(l->s, l->buf, &l->j);
	ft_strdel(&l->s);
	if (i[5] == 1)
		putnc_in_buf(i[2], ' ', l->buf, &l->j);
}

static void	width_prec_o(t_printf *l, int *i, int j)
{
	if (i[7] == 0)
		l->s = ft_itoa_base((unsigned int)l->lg[j], 8);
	else if (i[7] == 1)
		l->s = ft_itoa_base((unsigned short)l->lg[j], 8);
	else if (i[7] == 2)
		l->s = ft_itoa_base((unsigned char)l->lg[j], 8);
	else if (i[7] == 3)
		l->s = ft_itoa_base_u((unsigned long)l->lg[j], 8);
	else if (i[7] == 4)
		l->s = ft_itoa_base_u((unsigned long long)l->lg[j], 8);
	else if (i[7] == 5)
		l->s = ft_itoa_base_u((uintmax_t)l->lg[j], 8);
	else if (i[7] == 6)
		l->s = ft_itoa_base_u((size_t)l->lg[j], 8);
}

void		print_octal(t_printf *l, int *i, int j)
{
	width_prec_o(l, i, j);
	i[1] = (i[0] == 1) ? 0 : i[1];
	i[8] -= (i[3] == 1) ? 1 : 0;
	i[8] -= (l->lg[j] != 0) ? ft_strlen(l->s) : 0;
	i[8] = (i[8] < 0) ? 0 : i[8];
	i[2] -= (i[8] + ft_strlen(l->s) + ((i[3] == 1) ? 1 : 0));
	i[2] += ((i[0] == 1 || i[3] == 1) && l->lg[j] == 0) ? 1 : 0;
	if (i[5] == 0)
		putnc_in_buf(i[2], (i[1] == 1) ? '0' : ' ', l->buf, &l->j);
	if (i[3] == 1)
		putc_in_buf('0', l->buf, &l->j);
	putnc_in_buf(i[8], '0', l->buf, &l->j);
	if (!((i[0] == 1 || i[3] == 1) && l->lg[j] == 0))
		puts_in_buf(l->s, l->buf, &l->j);
	ft_strdel(&l->s);
	if (i[5] == 1)
		putnc_in_buf(i[2], ' ', l->buf, &l->j);
}
