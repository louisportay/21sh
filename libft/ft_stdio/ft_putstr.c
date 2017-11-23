/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 11:34:41 by lportay           #+#    #+#             */
/*   Updated: 2017/10/25 10:42:52 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Get the len of 's' and call write to print 's'.
*/

void	ft_putstr(char const *s)
{
	write(STDOUT_FILENO, s, ft_strlen(s));
}
