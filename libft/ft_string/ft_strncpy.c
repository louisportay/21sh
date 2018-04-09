/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 15:26:32 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/09 11:59:29 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char		*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*beg;

	beg = dst;
	while (len > 0 && *src)
	{
		*dst++ = *src++;
		len--;
	}
	while (len--)
		*dst++ = '\0';
	return (beg);
}
