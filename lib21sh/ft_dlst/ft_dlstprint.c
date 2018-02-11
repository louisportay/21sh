/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstprint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 10:58:56 by lportay           #+#    #+#             */
/*   Updated: 2018/02/11 16:28:16 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlst.h"
#include "ft_stdio.h"

/*
** Print the 'data' field with the given printing function
*/

void	ft_dlstprint(t_dlist *list, char *sep, void (*p)(void *))
{
	while (list)
	{
		p(list->data);
		ft_putstr(sep);
		list = list->next;
	}
}
