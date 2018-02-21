/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstaddr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 14:42:18 by lportay           #+#    #+#             */
/*   Updated: 2018/02/11 16:23:32 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlst.h"

t_dlist	*ft_dlstaddr(t_dlist *dlst, size_t rank)
{
	ft_dlsthead(&dlst);
	while (rank-- > 0)
		dlst = dlst->next;
	return (dlst);
}
