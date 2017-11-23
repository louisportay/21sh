/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 11:02:43 by lportay           #+#    #+#             */
/*   Updated: 2017/04/25 15:11:34 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		is_specifier(char c)
{
	if (c == 'C' || c == 'c' || c == 'O' || c == 'o' || c == 'S' || c == 's' ||
		c == 'D' || c == 'd' || c == 'X' || c == 'x' || c == 'U' || c == 'u' ||
			c == 'p' || c == '%' || c == 'i')
		return (1);
	return (0);
}

int		is_flag(char c)
{
	if (c == '.' || c == '#' || c == '+' || c == '-' || c == ' ' || c == '*' ||
		c == 'h' || c == 'l' || c == 'j' || c == 'z' || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int		is_arg(char *format)
{
	if (*format == '%')
		format++;
	else
		return (1);
	while (is_flag(*format) == 1)
		format++;
	if (is_specifier(*format) == 1)
		return (0);
	return (1);
}

int		is_oct_hex(int j)
{
	if (j == 'o' || j == 'O' || j == 'x' || j == 'X' || j == 'D' ||
			j == 'U' || j == 'u')
		return (1);
	return (0);
}
