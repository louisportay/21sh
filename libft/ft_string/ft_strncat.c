/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 15:45:14 by vbastion          #+#    #+#             */
/*   Updated: 2017/08/09 19:08:09 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*s;

	if (n == 0)
		return (s1);
	s = s1;
	while (*s1)
		s1++;
	while (1)
	{
		*(s1++) = *s2;
		if (*(s2++) == '\0')
			break ;
		if (--n == 0)
			break ;
	}
	if (*(s1 - 1) != '\0')
		*s1 = '\0';
	return (s);
}
