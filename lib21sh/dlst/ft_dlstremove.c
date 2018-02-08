/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstremove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 11:33:26 by lportay           #+#    #+#             */
/*   Updated: 2018/02/08 16:33:59 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include<stdio.h>
void		ft_dlstremove(t_dlist **alst, void (*del)(void **))
{
	t_dlist *tmp;
//	printf("alst %p - lst %p - data %s - next %p - prev %p\n", alst, *alst, (char *)(*alst)->data, (*alst)->next, (*alst)->prev);

	if ((*alst)->prev && (*alst)->next)
	{
		tmp = *alst;
		*alst = tmp->prev;
		printf("%p\n", tmp->next);//
		(*alst)->next = tmp->next;
		printf("%p\n", (*alst)->next);//
		(*alst)->next->prev = tmp->prev;//
		ft_dlstdelone(&tmp, del);
	}
	else if ((*alst)->prev && !(*alst)->next)
	{
		ft_putstr("Case 2\n");
		*alst = (*alst)->prev;
		ft_dlstdelone(&(*alst)->next, del);
	}
	else if ((*alst)->next && !(*alst)->prev)
	{
		ft_putstr("Case 3\n");
		*alst = (*alst)->next;
		ft_dlstdelone(&(*alst)->prev, del);
	}
	else if (!(*alst)->next && !(*alst)->prev)
	{
		ft_putstr("Case 4\n");
		ft_dlstdelone(alst, del);
	}
}
