/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstinsert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 11:34:05 by lportay           #+#    #+#             */
/*   Updated: 2017/05/11 17:43:03 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Insert the 'new' maillon after the 'rank' element in the list
** O(n) complexity
*/

void	ft_lstinsert(t_list **alst, size_t rank, t_list *new)
{
	t_list *tmp;
	t_list *tmp2;

	tmp = *alst;
	while (rank-- > 0)
		tmp = tmp->next;
	tmp2 = tmp->next;
	tmp->next = new;
	new->next = tmp2;
}
