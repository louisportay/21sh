/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:17:34 by lportay           #+#    #+#             */
/*   Updated: 2018/04/09 14:05:05 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlst.h"

/*
** This function only works for a 'string' data
*/

t_dlist	*ft_dlstdup(t_dlist *dlst)
{
	t_dlist *dup;

	if (!dlst)
		return (NULL);
	dup = NULL;
	ft_dlstend(&dlst);
	while (dlst)
	{
		if (ft_dlstnewadd(&dup, dlst->data, dlst->content_size, &ft_dlstnew)
				== -1)
		{
			ft_dlstdel(&dup, &delvoid);
			return (NULL);
		}
		dlst = dlst->prev;
	}
	return (dup);
}
