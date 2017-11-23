/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 11:34:41 by lportay           #+#    #+#             */
/*   Updated: 2017/10/19 16:57:00 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Insert the string 's' in the buffer 'buf' and then call write to 'fd'
** what's remaining in the buffer
*/

void	ft_putstr_fd(int fd, char const *s)
{
	size_t	i;

	i = ft_strlen(s);
	write(fd, s, i);
}
