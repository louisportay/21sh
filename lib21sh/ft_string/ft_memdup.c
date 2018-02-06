/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 18:24:01 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/06 16:04:46 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void			*ft_memdup(void *src, size_t n)
{
	void		*ret;

	if ((ret = malloc(n)) == NULL)
		return (NULL);
	return (ft_memcpy(ret, src, n));
}
