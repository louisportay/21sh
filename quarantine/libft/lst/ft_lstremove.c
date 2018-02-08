/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 11:33:26 by lportay           #+#    #+#             */
/*   Updated: 2017/10/23 12:41:52 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** O(N) complexity
** Delete the 'rank' element in the given list
*/

void	ft_lstremove(t_list **alst, size_t rank, void (*del)(void *, size_t))
{
	t_list *tmp;
	t_list *tmp2;

	tmp = *alst;
	if (rank != 0)
	{
		while (rank-- > 1)
			tmp = tmp->next;
		tmp2 = tmp->next;
		tmp->next = tmp->next->next;
		ft_lstdelone(&tmp2, del);
	}
	else
	{
		tmp2 = tmp->next;
		ft_lstdelone(&tmp, del);
		*alst = tmp2;
	}
}
