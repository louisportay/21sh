/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 11:27:56 by lportay           #+#    #+#             */
/*   Updated: 2017/04/25 15:14:45 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_percent(t_printf *l, int *i)
{
	i[2] -= 1;
	if (i[5] == 0)
		putnc_in_buf(i[2], (i[1] == 1) ? '0' : ' ', l->buf, &l->j);
	putc_in_buf('%', l->buf, &l->j);
	if (i[5] == 1)
		putnc_in_buf(i[2], ' ', l->buf, &l->j);
}

void	print_wstr(t_printf *l, int *i, wchar_t *wstr)
{
	if (!wstr)
		wstr = ft_wcsdup(L"(null)");
	i[2] -= bytewidth(wstr);
	if (i[0] == 1)
	{
		i[8] = max_wchar(wstr, i[8]);
		i[2] += ((bytewidth(wstr)) - i[8]);
	}
	if (i[5] == 0)
		putnc_in_buf(i[2], (i[1] == 1) ? '0' : ' ', l->buf, &l->j);
	(i[0] == 1) ? putnws_in_buf(wstr, &i[8], l->buf, &l->j) :
		putws_in_buf(wstr, l->buf, &l->j);
	if (i[5] == 1)
		putnc_in_buf(i[2], ' ', l->buf, &l->j);
}

void	print_str(t_printf *l, int *i, char *s)
{
	if (i[7] == 3)
		print_wstr(l, i, (wchar_t *)s);
	else
	{
		if (s)
			i[8] = (ft_strlen(s) < (size_t)i[8]) ? (int)ft_strlen(s) : i[8];
		else
		{
			s = ft_strdup("(null)");
			i[8] = (i[8] > 6) ? 6 : i[8];
			i[3] = 2;
		}
		i[2] -= (i[8] == 0 && i[0] == 0) ? (int)ft_strlen(s) : i[8];
		if (i[5] == 0)
			putnc_in_buf(i[2], (i[1] == 1) ? '0' : ' ', l->buf, &l->j);
		if (i[0] == 1)
			putns_in_buf(i[8], s, l->buf, &l->j);
		else if (i[0] == 0)
			puts_in_buf(s, l->buf, &l->j);
		if (i[3] == 2)
			ft_strdel(&s);
		if (i[5] == 1)
			putnc_in_buf(i[2], ' ', l->buf, &l->j);
	}
}

void	print_wchar(t_printf *l, int *i, long lg)
{
	if (lg <= 0x7F || (lg <= 0x7FF && MB_CUR_MAX == 1))
		i[2] -= 1;
	else if (lg <= 0x7FF)
		i[2] -= 2;
	else if (lg <= 0xFFFF)
		i[2] -= 3;
	else if (lg <= 0x1FFFFF)
		i[2] -= 4;
	if (i[5] == 0)
		putnc_in_buf(i[2], (i[1] == 1) ? '0' : ' ', l->buf, &l->j);
	putwc_in_buf(lg, l->buf, &l->j);
	if (i[5] == 1)
		putnc_in_buf(i[2], ' ', l->buf, &l->j);
}

void	print_char(t_printf *l, int *i, long lg)
{
	if (i[7] == 3)
		print_wchar(l, i, lg);
	else
	{
		i[2] -= 1;
		if (i[5] == 0)
			putnc_in_buf(i[2], (i[1] == 1) ? '0' : ' ', l->buf, &l->j);
		putc_in_buf(lg, l->buf, &l->j);
		if (i[5] == 1)
			putnc_in_buf(i[2], ' ', l->buf, &l->j);
	}
}
