/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 11:36:11 by lportay           #+#    #+#             */
/*   Updated: 2018/03/19 13:49:49 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlst.h"

void	ft_dlstadd(t_dlist **alst, t_dlist *new)
{
	new->next = *alst;
	if (*alst)
		(*alst)->prev = new;
	new->prev = NULL;
	*alst = new;
}
