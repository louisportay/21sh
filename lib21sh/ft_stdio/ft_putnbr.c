/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 11:14:19 by lportay           #+#    #+#             */
/*   Updated: 2018/02/06 16:43:26 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Ptet le remplacer par un truc plus efficient...?

void	ft_putnbr(long n)
{
	char *s;

	s = ft_itoa(n);
	ft_putstr(s);
	ft_strdel(&s);
}
