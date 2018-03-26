/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 17:19:29 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/25 20:19:24 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			fpf_handle_purestr(const char *str, size_t *i)
{
	size_t			beg;

	beg = *i;
	while (str[*i] != '\0' && str[*i] != '%' && str[*i] != '{')
		(*i)++;
	fpf_buf_add(str + beg, *i - beg);
}

static inline int	handle_format(const char *format, va_list ap)
{
	size_t			i;

	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			if (fpf_handle_flag(format, &i, ap) == -1)
				return (-1);
		}
		else
			fpf_handle_purestr(format, &i);
	}
	return (1);
}

int					fpf_worker(const char *format, va_list ap)
{
	int			ret;
	t_buf		*buf;

	buf = fpf_buf_get();
	fpf_buf_init(buf);
	if (handle_format(format, ap) == -1)
		return (-1);
	ret = buf->ret;
	fpf_buf_clear(buf);
	return (ret);
}
