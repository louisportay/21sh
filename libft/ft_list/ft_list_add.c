/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 18:20:13 by vbastion          #+#    #+#             */
/*   Updated: 2017/08/17 18:35:12 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void				list_add(t_list **head, t_list *elem)
{
	t_list			*curr;

	if (*head == NULL)
		*head = elem;
	else
	{
		curr = *head;
		while (curr->next == NULL)
			curr = curr->next;
		curr->next = elem;
	}
}

t_list				*list_addcontent(t_list **head, void *content)
{
	t_list			*elem;
	t_list			*curr;

	if ((elem = list_create(content)) == NULL)
		return (NULL);
	if (*head == NULL)
		*head = elem;
	else
	{
		curr = *head;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = elem;
	}
	return (elem);
}

t_list				*list_insert(t_list **head, void *content, int (*cmp)())
{
	t_list			*elem;
	t_list			*curr;
	t_list			*prev;

	if (cmp == NULL || head == NULL)
		return (NULL);
	if ((elem = list_create(content)) == NULL)
		return (NULL);
	if (*head == NULL)
		*head = elem;
	else
	{
		prev = *head;
		curr = prev->next;
		while (curr != NULL && prev != NULL
				&& cmp(elem->content, curr->content) > 0)
		{
			prev = curr;
			curr = curr->next;
		}
		prev->next = elem;
		elem->next = curr;
	}
	return (elem);
}
