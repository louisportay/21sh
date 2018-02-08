/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 15:10:31 by lportay           #+#    #+#             */
/*   Updated: 2017/04/24 19:27:55 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_flags(int *l)
{
	if (l[7] == 7)
		return (-1);
	l[1] = (l[5] == 1) ? 0 : l[1];
	l[6] = (l[4] == 1) ? 0 : l[6];
	if (l[9] == 'D' || l[9] == 'O' || l[9] == 'U')
		l[7] = 3;
	return (0);
}

int			check_input(char *format, t_printf *l)
{
	int i;

	i = 0;
	while (*format)
	{
		if (is_arg(format++) == 0 && l->first == true)
		{
			l->s = format;
			while (is_flag(*format))
			{
				if (!(*format >= '0' && *format <= '9') && *format != '*')
					get_flags(*format++, l->fl[i]);
				else
					get_width_prec(l, &format, l->fl[i]);
			}
			get_specifier(*format, l, i);
			if (l->fl[i][9] == 0 || check_flags(l->fl[i]) == -1)
				return (-1);
			l->first = false;
			i++;
		}
		else
			l->first = true;
	}
	return (0);
}

int			count_percent(char *format)
{
	int		nb;
	bool	first;

	first = true;
	nb = 0;
	while (*format)
	{
		if (is_arg(format++) == 0 && first == true)
		{
			nb += 1;
			first = false;
		}
		else
			first = true;
	}
	return (nb);
}
