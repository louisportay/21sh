/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 15:16:55 by lportay           #+#    #+#             */
/*   Updated: 2018/02/22 16:12:06 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  renvoie un pointeur vers le premier caractere 'c' trouvé sinon renvoie NULL
*/

#include "ft_string.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != c && *s != '\0')
		s++;
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

/*
**  renvoie un pointeur vers le dernier caractere 'c' trouvé sinon renvoie NULL
*/

#include "ft_string.h"

char	*ft_strrchr(const char *s, int c)
{
	char *tmp;

	tmp = (char *)s + ft_strlen(s);
	while (*tmp != c && tmp != s)
		tmp--;
	if (*tmp == c)
		return (tmp);
	else
		return (NULL);
}
