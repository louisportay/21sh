/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dec_rem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:22:02 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/10 16:25:29 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			handle_prefix_rem(t_flag *flag, u_char spec, char buf[3])
{
	if ((spec & 1) != 0)
		fpf_buf_addc('-');
	if ((spec & (1 << 1)) != 0)
		fpf_strcpy(buf, "0");
	if ((spec & (1 << 2)) != 0)
		fpf_strcpy(buf, flag->c == 'x' ? "0x" : "0X");
	if ((spec & (1 << 3)) != 0)
		fpf_strcpy(buf, "+");
	if ((spec & (1 << 4)) != 0)
		fpf_strcpy(buf, " ");
}

int					fpf_handle_prefix(t_flag *flag, u_char spec, size_t len)
{
	char		buf[3];
	size_t		sz;

	if ((flag->sz_flag & 2) != 0 && flag->pre <= len)
	{
		if (((flag->flag & (1 << 8))) && (flag->c == 'o' || flag->c == 'O'))
			fpf_buf_addc('0');
		return (pad_before(flag, len));
	}
	ft_bzero(buf, 3);
	handle_prefix_rem(flag, spec, buf);
	sz = fpf_strlen(buf);
	if ((flag->flag & (1 << 9)) == 0)
		pad_before(flag, len + sz);
	fpf_buf_add(buf, sz);
	if ((flag->flag & (1 << 9)) != 0)
		pad_before(flag, len + sz);
	return (sz);
}
