/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 17:39:24 by lportay           #+#    #+#             */
/*   Updated: 2017/10/25 16:21:15 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns the address of the 'n' maillon 
** return NULL if n negative
*/

t_list		*ft_lstaddr(t_list *lst, int n)
{
	if (n < 0)
		return (NULL);
	while (n-- > 0 && lst)
		lst = lst->next;
	return (lst);
}
