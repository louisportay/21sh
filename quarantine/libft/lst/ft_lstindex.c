/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 12:29:49 by lportay           #+#    #+#             */
/*   Updated: 2017/05/12 18:53:39 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** O(N) complexity
** The lstindex function seeks the index of 'maillon' in 'lst', if
** 'maillon' does not exist in 'lst', the returned value is the total number of
** maillons in the list.
*/

size_t		ft_lstindex(t_list *lst, t_list *maillon)
{
	size_t i;

	i = 0;
	while (lst != maillon && (lst = lst->next))
		i++;
	return ((!lst) ? i + 1 : i);
}
