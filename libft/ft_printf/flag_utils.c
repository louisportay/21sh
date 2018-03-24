/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 18:29:22 by vbastion          #+#    #+#             */
/*   Updated: 2017/08/07 18:32:19 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		fpf_flag_clear(t_flag *flag)
{
	flag->id = -1;
	flag->min = 0;
	flag->pre = 0;
	flag->sz_flag = 0;
	flag->flag = 0;
}
