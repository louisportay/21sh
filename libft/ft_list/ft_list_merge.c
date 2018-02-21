/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_merge.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 15:45:30 by vbastion          #+#    #+#             */
/*   Updated: 2017/08/17 18:27:44 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_list.h"

static inline void		push_back(t_list **list, t_list **head, t_list *elem)
{
	if (*list == NULL || *head == NULL)
	{
		*head = elem;
		*list = elem;
	}
	else
	{
		(*list)->next = elem;
		*list = elem;
	}
}

static inline t_list	*list_last(t_list *list)
{
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void					list_append(t_list **head, t_list *to_merge)
{
	t_list				*new_head;

	if (*head == NULL || to_merge == NULL)
		return ;
	new_head = list_last(to_merge);
	(*head)->next = to_merge;
	*head = new_head;
}

t_list					*list_merge(t_list *left, t_list *right, t_cmp cmp)
{
	t_list				*ret;
	t_list				*ret_head;
	t_list				*tmp;

	ret = NULL;
	ret_head = NULL;
	while (left != NULL && right != NULL)
	{
		if (cmp(left->content, right->content) < 0)
		{
			tmp = left->next;
			push_back(&ret, &ret_head, left);
			left = tmp;
		}
		else
		{
			tmp = right->next;
			push_back(&ret, &ret_head, right);
			right = tmp;
		}
	}
	list_append(&ret, left);
	list_append(&ret, right);
	return (ret_head);
}

t_list					*list_merge_sort(t_list *list, t_cmp cmp)
{
	t_list				*left;
	t_list				*right;
	t_list				*tmp;
	size_t				lengths[3];

	lengths[0] = ft_list_len(list);
	if (lengths[0] < 2)
		return (list);
	lengths[1] = lengths[0] / 2;
	lengths[2] = 0;
	left = NULL;
	right = NULL;
	while (list != NULL)
	{
		tmp = list->next;
		if (lengths[2] < lengths[1])
			list_push(&left, list);
		else
			list_push(&right, list);
		list = tmp;
		lengths[2]++;
	}
	left = list_merge_sort(left, cmp);
	right = list_merge_sort(right, cmp);
	return (list_merge(left, right, cmp));
}
