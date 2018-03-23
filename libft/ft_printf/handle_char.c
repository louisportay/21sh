/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 14:29:33 by vbastion          #+#    #+#             */
/*   Updated: 2017/08/26 14:07:05 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					fpf_handle_bch(va_list *ap, t_flag *flag)
{
	wint_t			wi;

	(void)flag;
	wi = (wint_t)va_arg(*ap, wint_t);
	if (wi > 0xFFFF && MB_CUR_MAX == 4)
	{
		fpf_buf_addc((0xF0 | ((wi & 0x1C0000) >> 18)));
		fpf_buf_addc((0x80 | ((wi & 0x3F000) >> 12)));
		fpf_buf_addc((0x80 | ((wi & 0xFC0) >> 6)));
		fpf_buf_addc((0x80 | (wi & 0x3F)));
	}
	else if (wi > 0x7FF && MB_CUR_MAX >= 3 && MB_CUR_MAX <= 4)
	{
		fpf_buf_addc((0xE0 | ((wi & 0xF000) >> 12)));
		fpf_buf_addc((0x80 | ((wi & 0xFC0) >> 6)));
		fpf_buf_addc((0x80 | (wi & 0x3F)));
	}
	else if (wi > 0x7F && MB_CUR_MAX >= 2 && MB_CUR_MAX <= 4)
	{
		fpf_buf_addc((0xC0 | ((wi & 0x7C0) >> 6)));
		fpf_buf_addc((0x80 | (wi & 0x3F)));
	}
	else if (MB_CUR_MAX >= 1 && MB_CUR_MAX <= 4 && wi <= 0x7F)
		fpf_buf_addc((wi & 0xFF) >> 24);
	return ((MB_CUR_MAX < 2 && wi > 0x7F) ? -1 : 1);
}

int					fpf_handle_char(va_list *ap, t_flag *flag)
{
	char			c;

	if (flag->flag == 8)
		fpf_handle_bch(ap, flag);
	else
	{
		c = (char)va_arg(*ap, int);
		pad_before(flag, 1);
		fpf_buf_add(&c, 1);
		pad_after(flag, 1);
	}
	return (1);
}
