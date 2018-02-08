/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 15:16:55 by lportay           #+#    #+#             */
/*   Updated: 2017/03/16 19:03:08 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  renvoie un pointeur vers le premier caractere 'c' trouvé sinon renvoie NULL
*/

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != c && *s != '\0')
		s++;
	if (*s == c)
		return ((char *)s);
	return (NULL);
}
