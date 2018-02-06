/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 12:08:41 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/06 16:04:42 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void			*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*cdst;
	char const	*csrc;
	size_t		i;

	cdst = (char *)dst;
	csrc = (char const *)src;
	i = 0;
	while (i < n)
	{
		*(cdst + i) = *(csrc + i);
		i++;
	}
	return (dst);
}
