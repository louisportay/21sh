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

char	*ft_strstr(const char *big, const char *little)
{
	char *tmp_b;
	char *tmp_l;

	if (ft_strlen(little) == 0 || big == little)
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
