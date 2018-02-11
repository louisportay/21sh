/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 20:16:16 by lportay           #+#    #+#             */
/*   Updated: 2018/02/11 16:23:37 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlst.h"

void	ft_dlstdelone(t_dlist **alst, void (*del)(void *, size_t))
{
	(*del)((*alst)->data, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
}
