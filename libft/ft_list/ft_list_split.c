/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 17:05:05 by vbastion          #+#    #+#             */
/*   Updated: 2017/08/15 12:59:10 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void				list_split(t_list **head, t_list **splitted,
								int (*assert)())
{
	t_list			*tmp_head;
	t_list			*new_head;
	t_list			*new_splitted;
	t_list			*tmp;

	tmp_head = *head;
	new_head = NULL;
	new_splitted = NULL;
	while (tmp_head != NULL)
	{
		tmp = tmp_head;
		tmp_head = tmp_head->next;
		if (assert(tmp->content))
			list_push(&new_splitted, tmp);
		else
			list_push(&new_head, tmp);
	}
	*splitted = new_splitted;
	*head = new_head;
}

void				list_split_data(t_list **head, t_list **splitted,
									int (*assert)(), void *data)
{
	t_list			*tmp_head;
	t_list			*new_head;
	t_list			*new_splitted;
	t_list			*tmp;

	tmp_head = *head;
	new_head = NULL;
	new_splitted = NULL;
	while (tmp_head != NULL)
	{
		tmp = tmp_head;
		tmp_head = tmp_head->next;
		if (assert(tmp->content, data))
			list_push(&new_splitted, tmp);
		else
			list_push(&new_head, tmp);
	}
	*splitted = new_splitted;
	*head = new_head;
}
