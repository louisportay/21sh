/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 17:43:06 by lportay           #+#    #+#             */
/*   Updated: 2017/06/10 17:44:03 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** O(n) complexity
*/

void	ft_lstmerge(t_list *lst1, t_list *lst2)
{
	t_list *tmp;

	tmp = ft_lstend(lst1);
	tmp->next = lst2;
}
