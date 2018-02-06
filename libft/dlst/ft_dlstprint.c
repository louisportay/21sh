/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstprint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 10:58:56 by lportay           #+#    #+#             */
/*   Updated: 2018/02/06 20:22:12 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstprint(t_dlist *dlst, char *sep, void	(*p)(void *data))
{
	while (dlst)
	{
		p(dlst->data);
		ft_putstr(sep);
		dlst = dlst->next;
	}
}
