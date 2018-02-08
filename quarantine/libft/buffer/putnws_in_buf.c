/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnws_in_buf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 14:55:30 by lportay           #+#    #+#             */
/*   Updated: 2017/04/24 18:32:46 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	putnws_in_buf2(wchar_t *j, int *n, char *buf, size_t *i)
{
	if ((j[0] <= 0xFFFF) && *n >= 3)
	{
		putc_in_buf((((j[2] >> 12) & FOUR_BITS) | 224), buf, i);
		putc_in_buf((((j[1] >> 6) & SIX_BITS) | 128), buf, i);
		putc_in_buf(((j[0] & SIX_BITS) | 128), buf, i);
		*n -= 3;
	}
	else if ((j[0] <= 0x1FFFFF) && *n >= 4)
	{
		putc_in_buf((((j[3] >> 18) & THREE_BITS) | 240), buf, i);
		putc_in_buf((((j[2] >> 12) & SIX_BITS) | 128), buf, i);
		putc_in_buf((((j[1] >> 6) & SIX_BITS) | 128), buf, i);
		putc_in_buf(((j[0] & SIX_BITS) | 128), buf, i);
		*n -= 4;
	}
}

void		putnws_in_buf(wchar_t *ws, int *n, char *buf, size_t *i)
{
	wchar_t j[4];

	while (*ws && *n > 0)
	{
		if (ft_isunicode(*ws) == -1)
			return ;
		fill_array(j, 4, *ws);
		if ((j[0] <= 0x7F || MB_CUR_MAX == 1) && *n >= 1)
		{
			putc_in_buf(j[0], buf, i);
			*n -= 1;
		}
		else if ((j[0] <= 0x7FF) && *n >= 2)
		{
			putc_in_buf((((j[1] >> 6) & FIVE_BITS) | 192), buf, i);
			putc_in_buf(((j[0] & SIX_BITS) | 128), buf, i);
			*n -= 2;
		}
		else
			putnws_in_buf2(j, n, buf, i);
		ws++;
	}
}
