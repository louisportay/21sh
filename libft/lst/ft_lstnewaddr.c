/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnewaddr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 19:18:14 by lportay           #+#    #+#             */
/*   Updated: 2017/10/18 16:16:32 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnewaddr(void const *content, size_t content_size)
{
	t_list	*maillon;

	if (!(maillon = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	maillon->next = NULL;
	if (!content)
	{
		maillon->content = NULL;
		maillon->content_size = 0;
		return (maillon);
	}
	maillon->content = (void *)content;
	maillon->content_size = content_size;
	return (maillon);
}
