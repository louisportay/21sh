/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstremove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 11:33:26 by lportay           #+#    #+#             */
/*   Updated: 2018/02/08 20:27:39 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_dlstremove(t_dlist **alst, void (*del)(void *, size_t))
{
	t_dlist *tmp;

	if ((*alst)->previous && (*alst)->next)
	{
		tmp = (*alst)->previous;
		tmp->next = tmp->next->next;
		ft_dlstdelone(&tmp->next->previous, del);
		tmp->next->previous = tmp;
		*alst = tmp;
	}
	else if ((*alst)->previous && !(*alst)->next)
	{
		*alst = (*alst)->previous;
		ft_dlstdelone(&(*alst)->next, del);
	}
	else if ((*alst)->next && !(*alst)->previous)
	{
		*alst = (*alst)->next;
		ft_dlstdelone(&(*alst)->previous, del);
	}
	else if (!(*alst)->next && !(*alst)->previous)
		ft_dlstdelone(alst, del);
}
