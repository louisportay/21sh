/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 11:36:50 by lportay           #+#    #+#             */
/*   Updated: 2017/03/16 19:17:02 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char *tmp;

	tmp = dst;
	while (len > 0 && *src != '\0')
	{
		*tmp++ = *src++;
		len--;
	}
	while (len > 0)
	{
		*tmp++ = '\0';
		len--;
	}
	return (dst);
}
