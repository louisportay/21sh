/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 10:51:58 by vbastion          #+#    #+#             */
/*   Updated: 2017/08/05 19:10:51 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int							pad_before(t_flag *flag, size_t str_len)
{
	int						sz;

	if ((flag->flag & (1 << 10)) != 0 || (flag->sz_flag & 1) == 0)
		return (1);
	sz = flag->min - (int)str_len;
	if (sz > 0)
		fpf_buf_addfillers((flag->flag & (1 << 9)) == 0, sz);
	return (1);
}

int							pad_after(t_flag *flag, size_t str_len)
{
	int						sz;

	if ((flag->flag & (1 << 10)) == 0 || (flag->sz_flag & 1) == 0)
		return (1);
	sz = flag->min - (int)str_len;
	if (sz > 0)
		fpf_buf_addfillers(1, sz);
	return (1);
}
