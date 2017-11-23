/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 11:30:35 by lportay           #+#    #+#             */
/*   Updated: 2017/05/10 21:40:48 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *tmp;
	t_list *new_lst;

	if (!lst || !*f)
		return (NULL);
	new_lst = (*f)(lst);
	tmp = new_lst;
	while (lst->next)
	{
		lst = lst->next;
		new_lst->next = (*f)(lst);
		if (!(new_lst->next))
			return (NULL);
		new_lst = new_lst->next;
	}
	new_lst = NULL;
	return (tmp);
}
