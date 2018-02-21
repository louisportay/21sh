/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_foreach.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/12 16:14:27 by vbastion          #+#    #+#             */
/*   Updated: 2017/08/17 18:38:51 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void	list_foreach(t_list *head, void (*iter)())
{
	while (head != NULL)
	{
		iter(head);
		head = head->next;
	}
}

void	list_foreach_if(t_list *head, void (*iter)(), int (*assert)())
{
	while (head != NULL)
	{
		if (assert == NULL || (assert != NULL && assert(head) != 0))
			iter(head);
		head = head->next;
	}
}

void	list_foreach_data(t_list *head, void (*iter)(), void *data)
{
	while (head != NULL)
	{
		iter(head, data);
		head = head->next;
	}
}

void	list_foreach_if_data(t_list *head, void (*iter)(), int (*assert)(),
								void *data)
{
	while (head != NULL)
	{
		if (assert == NULL || (assert != NULL && assert(head) != 0))
			iter(head, data);
		head = head->next;
	}
}
