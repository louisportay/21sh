/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstprint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 10:58:56 by lportay           #+#    #+#             */
/*   Updated: 2018/02/08 14:27:07 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>
void	ft_dlstprint(t_dlist *dlst, char *sep, void	(*p)(void *data))
{
	while (dlst)
	{
		printf("prev: %p cur: %p next: %p\n", dlst->prev, dlst, dlst->next); 
		p(dlst->data);
		ft_putstr(sep);
		dlst = dlst->next;
	}
}
