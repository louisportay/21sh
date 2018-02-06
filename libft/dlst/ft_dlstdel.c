/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 20:24:29 by lportay           #+#    #+#             */
/*   Updated: 2018/02/06 19:36:12 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstdel(t_dlist **alst, void (*del)(void **))
{
	t_dlist *tmp;

	tmp = *alst;
	while (tmp)
	{
		*alst = (*alst)->next;
		(*del)(tmp->data);
		free(tmp);
		tmp = *alst;
	}
	*alst = NULL;
}
