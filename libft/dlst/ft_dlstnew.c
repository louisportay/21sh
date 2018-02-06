/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnewaddr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 19:18:14 by lportay           #+#    #+#             */
/*   Updated: 2018/02/06 20:08:10 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstnew(void const *data)
{
	t_dlist	*maillon;

	if (!(maillon = malloc(sizeof(t_dlist))))
		return (NULL);
	maillon->prev = NULL;
	maillon->next = NULL;
	maillon->data = (void *)data;
	return (maillon);
}
