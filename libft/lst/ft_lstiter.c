/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 11:21:55 by lportay           #+#    #+#             */
/*   Updated: 2017/05/10 21:40:48 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list *tmp;

	if (lst && *f)
	{
		tmp = lst;
		while (tmp)
		{
			lst = lst->next;
			(*f)(tmp);
			tmp = lst;
		}
	}
}
