/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_next.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 18:30:35 by vbastion          #+#    #+#             */
/*   Updated: 2017/11/22 18:34:22 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

t_list				*ft_list_next(t_list *list, t_list **prev,
									int (*assert)(void *))
{
	*prev = NULL;
	while (list != NULL)
	{
		if (assert(list->content))
			return (list);
		*prev = list;
		list = list->next;
	}
	return (NULL);
}
