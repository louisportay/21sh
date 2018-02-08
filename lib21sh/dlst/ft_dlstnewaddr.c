/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnewaddr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 19:18:14 by lportay           #+#    #+#             */
/*   Updated: 2018/02/08 20:19:26 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstnewaddr(void const *data, size_t content_size)
{
	t_dlist	*maillon;

	if (!(maillon = malloc(sizeof(t_dlist))))
		return (NULL);
	maillon->prev = NULL;
	maillon->next = NULL;
	maillon->data = (void *)data;
	if (!data)
		maillon->content_size = 0;
	else
		maillon->content_size = content_size;
	return (maillon);
}
