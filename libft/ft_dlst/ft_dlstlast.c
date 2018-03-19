/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstlast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 18:40:19 by lportay           #+#    #+#             */
/*   Updated: 2018/03/19 13:51:53 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlst.h"

t_dlist	*ft_dlstlast(t_dlist *dlst)
{
	while (dlst->next)
		dlst = dlst->next;
	return (dlst);
}
