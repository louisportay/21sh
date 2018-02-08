/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putwc_in_buf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:06:58 by lportay           #+#    #+#             */
/*   Updated: 2017/04/24 18:33:13 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	putwc_in_buf(wchar_t a, char *buf, size_t *i)
{
	wchar_t j[3];

	if (ft_isunicode(a) == -1)
		return ;
	fill_array(j, 3, a);
	if (a <= 0x7F || MB_CUR_MAX == 1)
		putc_in_buf(a, buf, i);
	else if (a <= 0x7FF)
	{
		putc_in_buf((((j[1] >> 6) & FIVE_BITS) | 192), buf, i);
		putc_in_buf(((j[0] & SIX_BITS) | 128), buf, i);
	}
	else if (a <= 0xFFFF)
	{
		putc_in_buf((((j[2] >> 12) & FOUR_BITS) | 224), buf, i);
		putc_in_buf((((j[1] >> 6) & SIX_BITS) | 128), buf, i);
		putc_in_buf(((j[0] & SIX_BITS) | 128), buf, i);
	}
	else if (a <= 0x1FFFFF)
	{
		putc_in_buf((((a >> 18) & THREE_BITS) | 240), buf, i);
		putc_in_buf((((j[2] >> 12) & SIX_BITS) | 128), buf, i);
		putc_in_buf((((j[1] >> 6) & SIX_BITS) | 128), buf, i);
		putc_in_buf(((j[0] & SIX_BITS) | 128), buf, i);
	}
}
