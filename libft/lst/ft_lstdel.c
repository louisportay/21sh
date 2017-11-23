/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 20:24:29 by lportay           #+#    #+#             */
/*   Updated: 2017/05/11 17:34:41 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Destroy in a safe way the whole list, no possible memory leaks
*/

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;

	tmp = *alst;
	while (tmp)
	{
		*alst = (*alst)->next;
		(*del)(tmp->content, tmp->content_size);
		free(tmp);
		tmp = *alst;
	}
	free(*alst);
	*alst = NULL;
}
