/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 13:35:22 by lportay           #+#    #+#             */
/*   Updated: 2017/04/24 18:47:59 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa_base(long value, int base)
{
	char			*tmp;
	char			*s;
	long			pow;

	if (base == 10)
		return (ft_itoa(value));
	if (value < 0 || base < 2 || base > 16)
		return (NULL);
	pow = 1;
	while ((value / pow) >= base)
		pow *= base;
	if (!(s = (char *)malloc(sizeof(char) * (ft_bwidth(value, base) + 1))))
		return (NULL);
	tmp = s;
	while (value > 0)
	{
		*s++ = (value / pow) + ((value / pow < 10) ? '0' : 55);
		value -= ((value / pow) * pow);
		pow /= base;
	}
	pow *= base;
	while ((pow /= base) != 0)
		*s++ = '0';
	*s = '\0';
	return (tmp);
}
