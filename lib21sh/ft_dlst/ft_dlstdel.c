/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 20:24:29 by lportay           #+#    #+#             */
/*   Updated: 2018/02/11 16:23:35 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlst.h"

void	ft_dlstdel(t_dlist **alst, void (*del)(void *, size_t))
{
	t_dlist *tmp;

	tmp = *alst;
	while (tmp)
	{
		*alst = (*alst)->next;
		(*del)(tmp->data, tmp->content_size);
		free(tmp);
		tmp = *alst;
	}
	*alst = NULL;
}
