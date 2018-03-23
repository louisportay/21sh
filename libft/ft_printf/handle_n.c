/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_n.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 17:33:25 by vbastion          #+#    #+#             */
/*   Updated: 2017/08/10 09:41:18 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					fpf_handle_n(va_list *ap, t_flag *flag)
{
	int				*ptr;

	(void)flag;
	ptr = va_arg(*ap, int *);
	*ptr = fpf_buf_gettotal(NULL);
	return (1);
}
