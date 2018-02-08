/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 11:27:33 by exam              #+#    #+#             */
/*   Updated: 2017/03/30 13:46:23 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_esc(char c)
{
	if (c == ' ' || c == '\n' || c == '\v' || c == '\f' || c == '\r' ||
			c == '\t')
		return (1);
	return (0);
}

static int	is_nb(char c, int base)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if (c >= 'a' && c <= (base + 86))
		return (1);
	else if (c >= 'A' && c <= (base + 54))
		return (1);
	return (0);
}

int			ft_atoi_base(char *str, int base)
{
	long	nb;
	int		sign;

	nb = 0;
	sign = 1;
	if (base <= 1 || base >= 17)
		return (0);
	while (is_esc(*str))
		str++;
	sign = (*str == '-') ? -1 : sign;
	str = (*str == '-' || *str == '+') ? str + 1 : str;
	if (base >= 2 && base <= 10)
		while (*str >= '0' && *str <= (base - 1 + 48))
			nb = (nb * base) + *str++ - '0';
	else if (base >= 11 && base <= 16)
		while (is_nb(*str, base))
		{
			if (*str >= '0' && *str <= '9')
				nb = (nb * base) + *str++ - '0';
			else if (*str >= 'a' && *str <= (base + 86))
				nb = (nb * base) + *str++ + 10 - 'a';
			else if (*str >= 'A' && *str <= (base + 54))
				nb = (nb * base) + *str++ + 10 - 'A';
		}
	return (nb * sign);
}
