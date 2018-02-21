/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stroccur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 09:46:05 by lportay           #+#    #+#             */
/*   Updated: 2018/02/11 13:34:53 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include "ft_ctype.h"

size_t	ft_stroccur(const char *s, char c)
{
	size_t i;

	if (!s || ft_isprint(c) == 0)
		return (0);
	i = 0;
	while (*s)
		if (*s++ == c)
			i++;
	return (i);
}
