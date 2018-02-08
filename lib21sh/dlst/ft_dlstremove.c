/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstremove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 11:33:26 by lportay           #+#    #+#             */
/*   Updated: 2018/02/08 20:36:42 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_dlstremove(t_dlist **alst, void (*del)(void *, size_t))
{
	t_dlist *tmp;

	if ((*alst)->prev && (*alst)->next)
	{
		tmp = (*alst)->prev;
		tmp->next = tmp->next->next;
		ft_dlstdelone(&tmp->next->prev, del);
		tmp->next->prev = tmp;
		*alst = tmp;
	}
	else if ((*alst)->prev && !(*alst)->next)
	{
		*alst = (*alst)->prev;
		ft_dlstdelone(&(*alst)->next, del);
	}
	else if ((*alst)->next && !(*alst)->prev)
	{
		*alst = (*alst)->next;
		ft_dlstdelone(&(*alst)->prev, del);
	}
	else if (!(*alst)->next && !(*alst)->prev)
		ft_dlstdelone(alst, del);
}
