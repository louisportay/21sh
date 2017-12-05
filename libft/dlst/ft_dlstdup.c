/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 16:17:34 by lportay           #+#    #+#             */
/*   Updated: 2017/12/04 16:21:13 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** This function only works for a 'string' content 
*/

t_dlist *ft_dlstdup(t_dlist *dlst)
{
	t_dlist *dup;

	if (!dlst)
		return (NULL);
	dup = NULL;
	ft_dlstend(&dlst);
	while (dlst)
	{
		ft_dlstadd(&dup, ft_dlstnew(dlst->content, dlst->content_size));
		dlst = dlst->previous;
	}
	return (dup);
}
