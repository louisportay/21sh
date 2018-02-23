/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 11:45:43 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/22 17:22:56 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ctype.h"

int				ft_isnumber(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (ft_isdigit(*str) == 0)
		return (0);
	while (*str != '\0')
	{
		if (ft_isdigit((int)(*str)) == 0)
			return (0);
		str++;
	}
	return (1);
}
