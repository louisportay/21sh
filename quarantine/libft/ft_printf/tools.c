/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 14:45:45 by lportay           #+#    #+#             */
/*   Updated: 2017/04/24 19:27:56 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

wchar_t		*ft_strchr_greater(const wchar_t *s, int c)
{
	if (!s)
		return (NULL);
	while (*s < c && *s != '\0')
		s++;
	if (*s >= c)
		return ((wchar_t *)s);
	return (NULL);
}

size_t		bytewidth(wchar_t *wstr)
{
	size_t	i;

	i = 0;
	while (*wstr)
	{
		if (*wstr <= 0x7F || (*wstr <= 0x7FF && MB_CUR_MAX == 1))
			i += 1;
		else if (*wstr <= 0x7FF)
			i += 2;
		else if (*wstr <= 0xFFFF)
			i += 3;
		else if (*wstr <= 0x1FFFFF)
			i += 4;
		wstr++;
	}
	return (i);
}

static void	change_value(int *i, int *j, char a)
{
	*i -= a;
	*j += a;
}

int			max_wchar(wchar_t *wstr, int i)
{
	int j;

	j = 0;
	while (*wstr && i > 0)
	{
		if (*wstr <= 0x7F && i >= 1)
			change_value(&i, &j, 1);
		else if (*wstr <= 0x77F && i >= 2)
			change_value(&i, &j, 2);
		else if (*wstr <= 0xFFFF && i >= 3)
			change_value(&i, &j, 3);
		else if (*wstr <= 0x1FFFFF && i >= 4)
			change_value(&i, &j, 4);
		wstr++;
	}
	return (j);
}
