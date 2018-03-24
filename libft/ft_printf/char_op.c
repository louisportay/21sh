/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/30 12:40:36 by vbastion          #+#    #+#             */
/*   Updated: 2017/08/06 11:57:39 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int						fpf_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\v');
}

int						fpf_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int						fpf_isnum(int c)
{
	return (c >= '0' && c <= '9');
}

char					*fpf_strchr(const char *s, int c)
{
	char				cc;

	cc = (char)c;
	while (*s || *s == '\0')
	{
		if (*s == cc)
			return ((char *)s);
		if (*s == '\0')
			break ;
		s++;
	}
	return (NULL);
}
