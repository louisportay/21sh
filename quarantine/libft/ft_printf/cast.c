/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:39:19 by lportay           #+#    #+#             */
/*   Updated: 2017/05/12 15:25:23 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			cast_d(t_printf *l, int i, int j)
{
	l->lg[i] = 0;
	if (j == 'p')
		l->lg[i] |= va_arg(l->ap, unsigned long);
	else if (l->fl[i][7] == 3)
		l->lg[i] |= va_arg(l->ap, long);
	else if (l->fl[i][7] == 0 && is_oct_hex(j) == 0)
		l->lg[i] |= va_arg(l->ap, int);
	else if (l->fl[i][7] == 1 && is_oct_hex(j) == 0)
		l->lg[i] |= (short)va_arg(l->ap, int);
	else if (l->fl[i][7] == 2 && is_oct_hex(j) == 0)
		l->lg[i] |= (signed char)va_arg(l->ap, int);
	else if (l->fl[i][7] <= 2 && is_oct_hex(j) == 1)
		l->lg[i] |= va_arg(l->ap, long);
	else if (l->fl[i][7] == 4)
		l->lg[i] |= va_arg(l->ap, long long);
	else if (l->fl[i][7] == 5)
		l->lg[i] |= va_arg(l->ap, intmax_t);
	else if (l->fl[i][7] == 6)
		l->lg[i] |= va_arg(l->ap, ssize_t);
}

void			cast_s(t_printf *l, int i)
{
	if (l->fl[i][9] == 's')
		l->str[i] = va_arg(l->ap, char *);
	else if (l->fl[i][9] == 'c')
	{
		l->lg[i] = va_arg(l->ap, int);
		if (l->fl[i][7] == 3)
			if (l->lg[i] > 255 && MB_CUR_MAX == 1)
				l->fl[i][9] = 0;
	}
	else if (l->fl[i][9] == 'S')
	{
		l->wstr[i] = va_arg(l->ap, wchar_t *);
		if (ft_strchr_greater(l->wstr[i], 255) && MB_CUR_MAX == 1)
			l->fl[i][9] = 0;
	}
	else if (l->fl[i][9] == 'C')
	{
		l->lg[i] = va_arg(l->ap, wchar_t);
		if (l->lg[i] > 255 && MB_CUR_MAX == 1)
			l->fl[i][9] = 0;
	}
}
