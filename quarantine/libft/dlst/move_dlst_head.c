/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_dlst_head.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 19:49:37 by lportay           #+#    #+#             */
/*   Updated: 2018/02/06 20:27:20 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		move_dlst_head(t_dlist **dlist, int mov)
{
	if (!mov)
		return (mov);
	if (mov > 0)
		while ((*dlist)->next && mov)
		{
			*dlist = (*dlist)->next;
			mov--;
		}
	else
		while ((*dlist)->prev && mov)
		{
			*dlist = (*dlist)->prev;
			mov++;
		}
	return (mov);
}
