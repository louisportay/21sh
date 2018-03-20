/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 13:35:22 by lportay           #+#    #+#             */
/*   Updated: 2018/03/19 14:54:22 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

int		ft_lwidth(long nb)
{
	int				width;
	unsigned long	nbr;

	nbr = (nb > 0) ? nb : -nb;
	width = (nb >= 0) ? 1 : 2;
	while ((nbr /= 10) != 0)
		width++;
	return (width);
}

char	*ft_itoa(long n)
{
	char			*s;
	unsigned int	m;
	int				i;

	i = ft_lwidth(n);
	m = (n < 0) ? -n : n;
	if (!(s = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	s[i--] = '\0';
	s[i--] = (m % 10) + '0';
	while ((m /= 10) != 0)
		s[i--] = (m % 10) + '0';
	s[0] = (n < 0) ? '-' : s[0];
	return (s);
}
