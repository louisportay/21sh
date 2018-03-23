/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 17:33:06 by vbastion          #+#    #+#             */
/*   Updated: 2017/08/09 17:18:13 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	get_size(wchar_t *str)
{
	size_t		i;
	size_t		sz;

	i = 0;
	sz = 0;
	while (str[i] != '\0')
	{
		sz += fpf_bigcharsize(str[i]);
		i++;
	}
	return (sz);
}

static int		bufferize(wchar_t *str, size_t max, char *buf,
							size_t *buf_sz)
{
	char		cbuf[4];
	size_t		sz;

	(*buf_sz) = 0;
	while (*str != '\0' && max > 0)
	{
		if (fpf_putcharbuf(*str, cbuf, &sz) == -1)
			return (-1);
		if ((sz < max && sz == 1) || (max > 0 && sz == 1))
			buf[(*buf_sz)++] = (char)(*str);
		else if (sz <= max)
		{
			fpf_strncpy(buf + *buf_sz, cbuf, sz);
			(*buf_sz) += sz;
		}
		str++;
		max -= ((sz > max) ? max : sz);
	}
	return (1);
}

static void		print_str(char *buf, size_t sz, t_flag *flag)
{
	size_t		tsz;

	tsz = (flag->sz_flag & 1) && flag->min > sz ? flag->min - sz : 0;
	if ((tsz != 0) && (flag->flag & (1 << 10)) == 0)
		fpf_buf_addfillers((flag->flag & (1 << 9)) == 0, tsz);
	fpf_buf_add(buf, sz);
	if ((tsz != 0) && (flag->flag & (1 << 10)) != 0)
		fpf_buf_addfillers(1, tsz);
}

int				fpf_handle_lst(va_list *ap, t_flag *flag)
{
	wchar_t		*str;
	size_t		len;
	char		buf[FT_PBSZ];
	size_t		buf_sz;

	str = va_arg(*ap, wchar_t *);
	if (str == NULL)
	{
		len = (flag->sz_flag & 6) != 0 && flag->pre < 6 ? flag->pre : 6;
		print_str("(null)", len, flag);
	}
	else
	{
		len = get_size(str);
		len = (flag->sz_flag & 6) != 0 ? flag->pre : len;
		if (bufferize(str, len, buf, &buf_sz) == -1)
			return (-1);
		print_str(buf, buf_sz, flag);
	}
	return (1);
}

int				fpf_handle_str(va_list *ap, t_flag *flag)
{
	char		*str;
	size_t		len;

	if (flag->flag == 8)
		fpf_handle_lst(ap, flag);
	else
	{
		str = va_arg(*ap, char *);
		if (str != NULL)
		{
			len = fpf_strlen(str);
			len = ((flag->sz_flag & 6) != 0)
					&& flag->pre < len ? flag->pre : len;
			print_str(str, len, flag);
		}
		else
		{
			len = (flag->sz_flag & 6) != 0 && flag->pre < 6 ? flag->pre : 6;
			print_str("(null)", len, flag);
		}
	}
	return (1);
}
