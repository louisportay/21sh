/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bwidth.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 15:48:04 by lportay           #+#    #+#             */
/*   Updated: 2017/04/24 18:57:42 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_bwidth(unsigned long value, int base)
{
	size_t width;

	width = 1;
	while ((value /= base) != 0)
		width++;
	return (width);
}
