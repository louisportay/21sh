/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcsdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 13:10:33 by lportay           #+#    #+#             */
/*   Updated: 2017/04/25 14:56:03 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

wchar_t		*ft_wcsdup(const wchar_t *s)
{
	wchar_t	*tmp;
	wchar_t	*dest;

	if (!(dest = (wchar_t *)malloc(sizeof(wchar_t) * (ft_wcslen(s) + 1))))
		return (NULL);
	tmp = dest;
	while (*s)
	{
		*dest = *s;
		s++;
		dest++;
	}
	*dest = '\0';
	return (tmp);
}
