/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 17:04:42 by vbastion          #+#    #+#             */
/*   Updated: 2017/08/09 17:18:05 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				fpf_handle_pct(va_list *ap, t_flag *flag)
{
	(void)ap;
	if ((flag->sz_flag & 1) != 0 && flag->min > 0
		&& (flag->flag & (1 << 10)) == 0)
	{
		if ((flag->flag & (1 << 9)) == 0)
			fpf_buf_addfillers(1, flag->min - 1);
		else if ((flag->sz_flag & (1 << 7)) != 0)
			fpf_buf_addfillers(0, flag->min - 1);
		else
			fpf_buf_addfillers(1, flag->min - 1);
	}
	fpf_buf_addc('%');
	if ((flag->sz_flag & 1) != 0 && flag->min > 0
		&& (flag->flag & (1 << 10)) != 0)
		fpf_buf_addfillers(1, flag->min - 1);
	return (1);
}
