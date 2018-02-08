/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 19:03:35 by lportay           #+#    #+#             */
/*   Updated: 2016/11/10 17:10:33 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstri(const char *big, const char *little, size_t i)
{
	char *tmp_b;

	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (i-- > 0)
		big++;
	tmp_b = (char *)big;
	while (*tmp_b++ == *little && *little != '\0')
		little++;
	if (*little == '\0')
		return ((char *)big);
	return (NULL);
}
