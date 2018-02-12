/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randstring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 19:00:42 by lportay           #+#    #+#             */
/*   Updated: 2018/02/11 19:02:16 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char 	*randstring(int len)
{
	char	charset[64];
	char 	*tmp;
	char 	*s;

	if (len <= 0)
		return (NULL);
	ft_strncpy(charset, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_", 64); 
	if (!(s = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	s[len] = '\0';
	tmp = s;
	while (*tmp)
		*tmp++ = charset[rand() % (64 - 1)];
	return (s);
}
