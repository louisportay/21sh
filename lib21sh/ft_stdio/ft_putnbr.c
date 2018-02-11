/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 11:14:19 by lportay           #+#    #+#             */
/*   Updated: 2018/02/11 15:25:46 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_string.h"

// Ptet le remplacer par un truc plus efficient...?

void	ft_putnbr(long n)
{
	char *s;

	s = ft_itoa(n);
	ft_putstr(s);
	ft_strdel(&s);
}
