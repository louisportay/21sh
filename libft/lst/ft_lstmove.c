/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 11:31:22 by lportay           #+#    #+#             */
/*   Updated: 2017/08/24 21:57:40 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** O(N) complexity
** This function take the 'rank' maillon of the list and insert it after the
** 'new_rank' maillon
** The two 'rank's must be different
*/

void	movehead(t_list **alst, t_list *tmp, t_list *tmp1, size_t nrank)
{
	*alst = tmp->next;
	tmp1 = tmp;
	while (nrank-- > 0)
		tmp1 = tmp1->next;
	tmp->next = tmp1->next;
	tmp1->next = tmp;
}

void	ft_lstmove(t_list **alst, size_t rank, size_t nrank)
{
	t_list *tmp;
	t_list *tmp1;
	t_list *tmp2;

	if (rank == nrank)
		return ;
	tmp = *alst;
	tmp1 = *alst;
	if (rank == 0)
		return (movehead(alst, tmp, tmp1, nrank));
	while (rank-- > 1)
		tmp = tmp->next;
	while (nrank-- > 0)
		tmp1 = tmp1->next;
	tmp2 = tmp->next;
	tmp->next = tmp->next->next;
	tmp2->next = tmp1->next;
	tmp1->next = tmp2;
}
