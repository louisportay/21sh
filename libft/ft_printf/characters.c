/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   characters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 14:51:14 by vbastion          #+#    #+#             */
/*   Updated: 2017/08/26 12:57:51 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t		fpf_countbits(u_int n)
{
	size_t			r;
	int				i;
	int				max;

	i = 0;
	r = 0;
	max = (sizeof(u_int) * 8);
	while (i < max)
	{
		if (n & 1)
			r = i + 1;
		n = (n >> 1);
		i++;
	}
	return (r);
}

int					fpf_bigcharsize(wint_t wi)
{
	size_t			cnt;
	int				mb_cur;

	cnt = fpf_countbits(wi);
	mb_cur = MB_CUR_MAX;
	if (cnt < 8)
		return (1);
	else if (cnt < 11 && mb_cur > 1)
		return (2);
	else if (cnt < 17 && mb_cur > 2)
		return (3);
	else if (cnt < 22 && mb_cur > 3)
		return (4);
	else
		return (-1);
}

static int			test_char_err(size_t cnt)
{
	int				mb_cur;

	mb_cur = MB_CUR_MAX;
	if (cnt < 8)
		return (1);
	else if (cnt < 11 && mb_cur > 1)
		return (2);
	else if (cnt < 17 && mb_cur > 2)
		return (3);
	else if (cnt < 22 && mb_cur > 3)
		return (4);
	else
		return (-1);
}

int					fpf_putcharbuf(wint_t wi, char buf[4], size_t *sz)
{
	size_t			bcnt;

	bcnt = fpf_countbits(wi);
	if (test_char_err(bcnt) == -1 || (wi >= 0xD800 && wi <= 0xDFFF))
		return (-(fpf_buf_clear(NULL)));
	if (bcnt < 12)
	{
		buf[0] = 0xC0 | ((wi & 0x7C0) >> 6);
		buf[1] = 0x80 | (wi & 0x3F);
		*sz = bcnt < 8 ? 1 : 2;
	}
	else if (bcnt > 11 && bcnt < 22)
	{
		buf[0] = bcnt < 17 ? (0xE0 | ((wi & 0xF000) >> 12)) :
			(0xF0 | ((wi & 0x1C0000) >> 18));
		buf[1] = bcnt < 17 ? (0x80 | ((wi & 0xFC0) >> 6)) :
			(0x80 | ((wi & 0x3F000) >> 12));
		buf[2] = bcnt < 17 ? (0x80 | (wi & 0x3F)) :
			(0x80 | ((wi & 0xFC0) >> 6));
		buf[3] = 0x80 | (wi & 0x3F);
		*sz = bcnt < 17 ? 3 : 4;
	}
	return (1);
}
