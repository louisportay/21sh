/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 14:53:43 by lportay           #+#    #+#             */
/*   Updated: 2018/02/11 16:23:33 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlst.h"

size_t	ft_dlstcount(t_dlist *dlst)
{
	size_t nb_maillons;

	nb_maillons = 0;
	ft_dlsthead(&dlst);
	while ((dlst = dlst->next))
		nb_maillons++;
	return (nb_maillons);
}
