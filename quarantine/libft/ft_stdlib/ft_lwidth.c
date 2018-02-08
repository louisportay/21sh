/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lwidth.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 18:41:47 by lportay           #+#    #+#             */
/*   Updated: 2017/04/25 13:24:05 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
