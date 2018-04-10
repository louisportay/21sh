/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnewadd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 12:42:13 by lportay           #+#    #+#             */
/*   Updated: 2018/04/10 12:03:36 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlst.h"

int		ft_dlstnewadd(t_dlist **lst, void *data, size_t size,
						t_dlist *(*new)(void const *, size_t))
{
	t_dlist *elem;

	if ((elem = new(data, size)) == NULL)
		return (-1);
	ft_dlstadd(lst, elem);
	return (0);
}

int		ft_dlstnewaddend(t_dlist *lst, void *data, size_t size,
						t_dlist *(*new)(void const *, size_t))
{
	t_dlist *elem;

	if ((elem = new(data, size)) == NULL)
		return (-1);
	ft_dlstaddend(lst, elem);
	return (0);
}
