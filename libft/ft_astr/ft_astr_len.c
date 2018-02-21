/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_astr_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:02:15 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/06 15:37:56 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_astr.h"

size_t			ft_astr_len(char **arr)
{
	size_t		len;

	if (arr == NULL)
		return (0);
	len = 0;
	while (arr[len] != NULL)
		len++;
	return (len);
}
