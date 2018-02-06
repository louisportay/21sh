/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 19:26:21 by lportay           #+#    #+#             */
/*   Updated: 2018/02/06 16:02:43 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Renvoie une chaîne mallocé de "size" caracteres + 1 ('\0' final)
*/

#include "ft_string.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	char	*tmp;

	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	tmp = str;
	while (size--)
		*str++ = '\0';
	*str = '\0';
	return (tmp);
}
