/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 15:35:22 by lportay           #+#    #+#             */
/*   Updated: 2017/04/25 15:15:26 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	mini_parsing(char **format, int *tmp)
{
	if (tmp[0] == 0 && **format == '0')
		tmp[1] = 1;
	if (**format == '-')
	{
		tmp[2] = 1;
		tmp[1] = 0;
	}
	if ((**format >= '1' && **format <= '9') ||
			(**format == '0' && tmp[0] != 0))
		tmp[0] = (tmp[0] * 10) + **format - '0';
	(*format)++;
}

static void	flag_in_buf_false_spec(t_printf *l, int *tmp)
{
	if (tmp[1] == 1)
		putnc_in_buf(tmp[0] - 1, '0', l->buf, &l->j);
	else
		putnc_in_buf(tmp[0] - 1, ' ', l->buf, &l->j);
	tmp[0] = 0;
}

static void	simple_char_in_buf(t_printf *l, char *format, int *tmp)
{
	putc_in_buf(*format, l->buf, &l->j);
	if (tmp[2] == 1)
	{
		putnc_in_buf(tmp[0] - 1, ' ', l->buf, &l->j);
		tmp[2] = 0;
	}
}

static void	wrap_print_arg(t_printf *l, int *i, char **format)
{
	print_argument(l, *i);
	if (l->fl[*i][9] == '%')
		(*format)++;
	while (**format != l->fl[*i][9])
		(*format)++;
	(*i)++;
}

void		print_input(t_printf *l, char *format, int *i)
{
	int tmp[3];

	tmp[2] = 0;
	*i = 0;
	while (*format)
	{
		if (is_arg(format) == 0)
			wrap_print_arg(l, i, &format);
		else
		{
			if (*format == '%')
			{
				fill_array(tmp, 3, 0);
				while (is_flag(*format) == 1 || *format == '%')
					mini_parsing(&format, tmp);
				if (tmp[2] == 0)
					flag_in_buf_false_spec(l, tmp);
				continue;
			}
			simple_char_in_buf(l, format, tmp);
		}
		format++;
	}
	write(1, &l->buf, l->j % BUFF_SIZE);
}
