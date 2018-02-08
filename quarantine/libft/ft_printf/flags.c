/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:37:12 by lportay           #+#    #+#             */
/*   Updated: 2017/08/23 17:51:28 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		get_specifier(char f, t_printf *l, int i)
{
	if (f == 's' || f == 'S' || f == 'p' || f == 'd' || f == 'D' || f == 'i' ||
			f == 'o' || f == 'O' || f == 'u' || f == 'U' ||
			f == 'x' || f == 'X' || f == 'c' || f == 'C' || f == '%')
		l->fl[i][9] = f;
	if (l->fl[i][9] == 's' || l->fl[i][9] == 'S' || l->fl[i][9] == 'c' ||
			l->fl[i][9] == 'C')
		cast_s(l, i);
	else if (l->fl[i][9] == 'p' || l->fl[i][9] == 'd' || l->fl[i][9] == 'D' ||
			l->fl[i][9] == 'i' || l->fl[i][9] == 'o' || l->fl[i][9] == 'O' ||
			l->fl[i][9] == 'u' || l->fl[i][9] == 'U' || l->fl[i][9] == 'x' ||
			l->fl[i][9] == 'X')
		cast_d(l, i, l->fl[i][9]);
}

void		get_format(char f, int *l)
{
	if (f == 'h')
	{
		if (l[7] == 1)
			l[7] = 2;
		else if (l[7] == 0)
			l[7] = 1;
	}
	else if (f == 'l')
	{
		if (l[7] == 3)
			l[7] = 4;
		else if (l[7] == 0)
			l[7] = 3;
	}
	else if (f == 'j')
		l[7] = 5;
	else if (f == 'z')
		l[7] = 6;
}

void		get_flags(char f, int *l)
{
	if (f == '.')
		l[0] = 1;
	else if (f == '#')
		l[3] = 1;
	else if (f == '+')
		l[4] = 1;
	else if (f == '-')
		l[5] = 1;
	else if (f == ' ')
		l[6] = 1;
	else if (f == 'h' || f == 'l' || f == 'j' || f == 'z')
		get_format(f, l);
}

static void	min_field_prec(char **f, int *l)
{
	if (**f == '0' && l[0] == 0 && l[2] == 0)
	{
		l[1] = 1;
		(*f)++;
	}
	if (**f >= '0' && **f <= '9')
	{
		if (l[0] == 1 && l[8] == 0)
		{
			l[8] = ft_atoi(*f);
			(*f) += ft_lwidth(l[8]);
		}
		else
		{
			l[2] = ft_atoi(*f);
			(*f) += ft_lwidth(l[2]);
		}
	}
	if (**f == '.')
	{
		l[0] = 1;
		(*f)++;
	}
}

void		get_width_prec(t_printf *i, char **f, int *l)
{
	min_field_prec(f, l);
	if (**f == '*')
	{
		if (l[0] == 1 && l[8] == 0)
		{
			l[8] = va_arg(i->ap, int);
			l[0] = (l[8] < 0) ? 0 : l[0];
		}
		else
			l[2] = va_arg(i->ap, int);
		if (l[2] < 0)
			l[5] = 1;
		l[2] = (l[2] < 0) ? -l[2] : l[2];
		(*f)++;
	}
}
