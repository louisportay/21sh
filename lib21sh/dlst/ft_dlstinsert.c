/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstinsert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 16:43:26 by lportay           #+#    #+#             */
/*   Updated: 2018/02/08 20:32:27 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstinsert(t_dlist *previous, t_dlist *between)
{
	t_dlist *next;

	next = previous->next;
	if (between->prev && between->next)
	{
		between->prev->next = between->next;
		between->next->prev = between->prev;
	}
	else if (between->prev)
		between->prev->next = NULL;
	else if (between->next)
		between->next->prev = NULL;
	previous->next = between;
	if (next)
		next->prev = between;
	between->next = next;
	between->prev = previous;
}
