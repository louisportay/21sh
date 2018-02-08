/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_dlst_head.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 19:49:37 by lportay           #+#    #+#             */
/*   Updated: 2018/02/08 20:27:54 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		move_dlst_head(t_dlist **dlist, int movement)
{
	if (!movement)
		return (movement);
	if (movement > 0)
		while ((*dlist)->next && movement)
		{
			*dlist = (*dlist)->next;
			movement--;
		}
	else
		while ((*dlist)->previous && movement)
		{
			*dlist = (*dlist)->previous;
			movement++;
		}
	return (movement);
}
