/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 17:42:31 by lportay           #+#    #+#             */
/*   Updated: 2018/02/06 16:02:43 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strcat(char *s1, const char *s2)
{
	char *tmp;

	tmp = s1;
	while (*s1)
		s1++;
	while (*s2)
		*s1++ = (unsigned char)*s2++;
	*s1 = '\0';
	return (tmp);
}
