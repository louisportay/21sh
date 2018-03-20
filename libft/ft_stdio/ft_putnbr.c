/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 11:14:19 by lportay           #+#    #+#             */
/*   Updated: 2018/03/19 14:41:31 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"
#include "ft_string.h"

/*
** vbastion:   Ptet le remplacer par un truc plus efficient...?
** lportay:	   Ouais bof.. De toute facon on s'en sert pas vraiment
*/

void	ft_putnbr(long n)
{
	char *s;

	s = ft_itoa(n);
	ft_putstr(s);
	free(s);
}
