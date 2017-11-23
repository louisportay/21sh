/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_u.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 13:10:16 by lportay           #+#    #+#             */
/*   Updated: 2017/04/25 13:12:50 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base_u(unsigned long value, unsigned int base)
{
	char			*tmp;
	char			*s;
	unsigned long	pow;

	if (base < 2 || base > 16)
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
