/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstfirst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 18:40:19 by lportay           #+#    #+#             */
/*   Updated: 2018/03/23 14:15:35 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlst.h"

t_dlist	*ft_dlstfirst(t_dlist *dlst)
{
	while (dlst->prev)
		dlst = dlst->prev;
	return (dlst);
}
