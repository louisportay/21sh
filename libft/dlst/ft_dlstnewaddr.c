/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnewaddr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 19:18:14 by lportay           #+#    #+#             */
/*   Updated: 2017/11/23 11:28:03 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstnewaddr(void const *content, size_t content_size)
{
	t_dlist	*maillon;

	if (!(maillon = malloc(sizeof(t_dlist))))
		return (NULL);
	maillon->previous = NULL;
	maillon->next = NULL;
	maillon->content = (void *)content;
	if (!content)
		maillon->content_size = 0;
	else
		maillon->content_size = content_size;
	return (maillon);
}
