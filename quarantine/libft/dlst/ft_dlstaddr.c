/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstaddr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 14:42:18 by lportay           #+#    #+#             */
/*   Updated: 2017/11/17 16:21:09 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstaddr(t_dlist *dlst, size_t rank)
{
	ft_dlsthead(&dlst);
	while (rank-- > 0)
		dlst = dlst->next;
	return (dlst);
}
