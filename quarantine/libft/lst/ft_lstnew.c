/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 19:18:14 by lportay           #+#    #+#             */
/*   Updated: 2017/10/18 16:16:58 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*maillon;
	char	*s;

	if (!(maillon = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	maillon->next = NULL;
	if (!content)
	{
		maillon->content = NULL;
		maillon->content_size = 0;
		return (maillon);
	}
	if (!(s = (char *)malloc(sizeof(char) * content_size)))
		return (NULL);
	ft_memcpy(s, content, content_size);
	maillon->content = s;
	maillon->content_size = content_size;
	return (maillon);
}
