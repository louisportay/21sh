/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 13:43:22 by lportay           #+#    #+#             */
/*   Updated: 2017/08/23 17:51:11 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** . -> 0
** 0 -> 1
** MFW -> 2
** # -> 3
** + -> 4
** - -> 5
** ' '-> 6
** format (hh 2, h 1, l 3, ll 4, j 5, z 6) -> 7
** prec -> 8
** specifier (d D o x C...) -> 9
** short (int) -> 10
*/

#include "ft_printf.h"

void		print_argument(t_printf *l, int i)
{
	if (l->fl[i][9] == 'd' || l->fl[i][9] == 'i' || l->fl[i][9] == 'D')
		print_d(l, l->fl[i], i);
	else if (l->fl[i][9] == 'o' || l->fl[i][9] == 'O')
		print_octal(l, l->fl[i], i);
	else if (l->fl[i][9] == 'x' || l->fl[i][9] == 'X')
		print_hexa(l, l->fl[i], i);
	else if (l->fl[i][9] == 'u' || l->fl[i][9] == 'U')
		print_unsigned(l, l->fl[i], i);
	else if (l->fl[i][9] == 's')
		print_str(l, l->fl[i], l->str[i]);
	else if (l->fl[i][9] == 'c')
		print_char(l, l->fl[i], l->lg[i]);
	else if (l->fl[i][9] == 'p')
		print_pointer(l, l->fl[i], i);
	else if (l->fl[i][9] == 'S')
		print_wstr(l, l->fl[i], l->wstr[i]);
	else if (l->fl[i][9] == 'C')
		print_wchar(l, l->fl[i], l->lg[i]);
	else if (l->fl[i][9] == '%')
		print_percent(l, l->fl[i]);
}

static int	mallocate(t_printf *l, int i)
{
	if (!(l->fl = ft_darray(i, 10)))
		return (-1);
	fill_darray(l->fl, i, 10, 0);
	if (!(l->lg = (long *)malloc(sizeof(long) * i)))
		return (-1);
	if (!(l->str = (char **)malloc(sizeof(char *) * i)))
		return (-1);
	if (!(l->wstr = (wchar_t **)malloc(sizeof(wchar_t *) * i)))
		return (-1);
	return (0);
}

static void	unmallocate(t_printf *l, int i)
{
	while (i--)
		free(l->fl[i]);
	free(l->fl);
	free(l->lg);
	free(l->str);
	free(l->wstr);
}

int			ft_printf(const char *restrict format, ...)
{
	t_printf	l;
	size_t		tmp;
	int			i;

	l.j = 0;
	i = count_percent((char *)format);
	if (mallocate(&l, i) == -1)
		return (-1);
	va_start(l.ap, format);
	l.first = true;
	if (check_input((char *)format, &l) == -1)
	{
		va_end(l.ap);
		unmallocate(&l, i);
		return (-1);
	}
	print_input(&l, (char *)format, &i);
	va_end(l.ap);
	tmp = l.j;
	unmallocate(&l, i);
	return (tmp);
}
