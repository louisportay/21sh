/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 19:18:14 by lportay           #+#    #+#             */
/*   Updated: 2018/02/08 20:32:39 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstnew(void const *data, size_t content_size)
{
	t_dlist	*maillon;
	char	*s;

	if (!(maillon = malloc(sizeof(t_dlist))))
		return (NULL);
	maillon->prev = NULL;
	maillon->next = NULL;
	if (!data)
	{
		maillon->data = NULL;
		maillon->content_size = 0;
		return (maillon);
	}
	if (!(s = (char *)malloc(sizeof(char) * (content_size + 1))))
		return (NULL);
	ft_memcpy(s, data, content_size);
	s[content_size] = '\0';
	maillon->data = s;
	maillon->content_size = content_size;
	return (maillon);
}
