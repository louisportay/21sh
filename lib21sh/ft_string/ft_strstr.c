/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 19:03:35 by lportay           #+#    #+#             */
/*   Updated: 2018/02/11 13:24:40 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
** man 3 strstr
*/

char	*ft_strstr(const char *big, const char *little)
{
	char *tmp_b;
	char *tmp_l;

	if (!ft_strlen(little) || big == little)
		return ((char *)big);
	while (*big)
	{
		tmp_b = (char *)big;
		tmp_l = (char *)little;
		while (*tmp_b++ == *tmp_l && *tmp_l != '\0')
			tmp_l++;
		if (*tmp_l == '\0')
			return ((char *)big);
		big++;
	}
	return (NULL);
}
