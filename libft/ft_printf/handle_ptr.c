/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 13:57:25 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/26 17:23:35 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				fpf_handle_ptr(va_list *ap, t_flag *flag)
{
	void		*ptr;
	char		*buf;
	size_t		len;

	buf = fpf_buf_get()->tmp_buf;
	ptr = va_arg(*ap, void *);
	ft_bzero(buf, 65);
	ft_ultobuf((u_long)ptr, 16, 0, buf);
	len = fpf_strlen(buf);
	if ((flag->flag & (1 << 9)) == 0)
		pad_before(flag, len + 2);
	fpf_buf_add("0x", 2);
	if ((flag->flag & (1 << 9)) != 0)
		pad_before(flag, len + 2);
	if (ptr != NULL)
	{
		if ((flag->sz_flag & 6) != 0 && (size_t)flag->pre > len)
			fpf_buf_addfillers(0, flag->pre - len);
		fpf_buf_add(buf, len);
	}
	else if ((flag->sz_flag & 6) == 6)
		fpf_buf_addfillers(0, flag->pre);
	else
		fpf_buf_addc('0');
	pad_after(flag, len + 2);
	return (1);
}
