/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_unsigned.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:05:53 by lportay           #+#    #+#             */
/*   Updated: 2017/08/23 17:51:51 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_itoa_unsigned(unsigned long nbr)
{
	int				i;
	char			*s;
	unsigned long	m;

	m = nbr;
	if (!(s = (char *)malloc(sizeof(char) * (ft_bwidth(nbr, 10) + 1))))
		return (NULL);
	i = 0;
	s[i++] = (m % 10) + '0';
	while ((m /= 10) != 0)
		s[i++] = (m % 10) + '0';
	s[i] = '\0';
	ft_strrev(s);
	return (s);
}

static void	width_prec_u(t_printf *l, long lg, int *i)
{
	if (i[7] == 0)
		l->s = ft_itoa_unsigned((unsigned int)lg);
	else if (i[7] == 1)
		l->s = ft_itoa_unsigned((unsigned short)lg);
	else if (i[7] == 2)
		l->s = ft_itoa_unsigned((unsigned char)lg);
	else if (i[7] == 3)
		l->s = ft_itoa_unsigned((unsigned long)lg);
	else if (i[7] == 4)
		l->s = ft_itoa_unsigned((unsigned long long)lg);
	else if (i[7] == 5)
		l->s = ft_itoa_unsigned((uintmax_t)lg);
	else if (i[7] == 6)
		l->s = ft_itoa_unsigned((size_t)lg);
}

void		print_unsigned(t_printf *l, int *i, int j)
{
	width_prec_u(l, l->lg[j], i);
	i[2] -= (ft_strlen(l->s) > (size_t)i[8]) ? (int)ft_strlen(l->s) : i[8];
	i[8] -= ft_strlen(l->s);
	i[1] = (i[0] == 1) ? 0 : i[1];
	if (i[5] == 0)
		putnc_in_buf(i[2], (i[1] == 1) ? '0' : ' ', l->buf, &l->j);
	if (i[0] == 1)
		putnc_in_buf(i[8], '0', l->buf, &l->j);
	if (!(l->lg[j] == 0 && i[0] == 1))
		puts_in_buf(l->s, l->buf, &l->j);
	ft_strdel(&l->s);
	if (i[5] == 1)
		putnc_in_buf(i[2], ' ', l->buf, &l->j);
}

static void	width_prec_d(long lg, int *i)
{
	i[1] = (i[0] == 1) ? 0 : i[1];
	i[8] -= (lg != 0) ? ft_lwidth(lg) : 0;
	i[8] += (lg < 0) ? 1 : 0;
	i[8] = (i[8] < 0) ? 0 : i[8];
	i[2] -= i[8] + ft_lwidth(lg);
	i[2] -= (((i[4] == 1 || i[6] == 1) && lg >= 0) ? 1 : 0);
	i[2] += (lg == 0 && i[0] == 1) ? 1 : 0;
}

void		print_d(t_printf *l, int *i, int j)
{
	l->s = ft_itoa_unsigned((l->lg[j] < 0) ? -(l->lg[j]) : l->lg[j]);
	width_prec_d(l->lg[j], i);
	if (i[5] == 0 && i[1] == 0)
		putnc_in_buf(i[2], ' ', l->buf, &l->j);
	if (l->lg[j] < 0)
		putc_in_buf('-', l->buf, &l->j);
	else if (i[4] == 1)
		putc_in_buf('+', l->buf, &l->j);
	else if (i[6] == 1)
		putc_in_buf(' ', l->buf, &l->j);
	putnc_in_buf(i[8], '0', l->buf, &l->j);
	if (i[1] == 1)
		putnc_in_buf(i[2], '0', l->buf, &l->j);
	if (l->lg[j] != 0 || i[0] != 1)
		puts_in_buf(l->s, l->buf, &l->j);
	ft_strdel(&l->s);
	if (i[5] == 1 && i[2] > 0)
		putnc_in_buf(i[2], ' ', l->buf, &l->j);
}
