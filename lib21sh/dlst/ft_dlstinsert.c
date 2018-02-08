/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstinsert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 16:43:26 by lportay           #+#    #+#             */
/*   Updated: 2018/02/08 20:26:19 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstinsert(t_dlist *previous, t_dlist *between)
{
	t_dlist *next;

	next = previous->next;
	if (between->previous && between->next)
	{
		between->previous->next = between->next;
		between->next->previous = between->previous;
	}
	else if (between->previous)
		between->previous->next = NULL;
	else if (between->next)
		between->next->previous = NULL;
	previous->next = between;
	if (next)
		next->previous = between;
	between->next = next;
	between->previous = previous;
}
