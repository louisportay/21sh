/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list_bridge.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:02:39 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/05 14:01:32 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"

void			ft_list_insert(t_list **head, t_list **curr, t_list *elem)
{
	if (*head == NULL)
	{
		*head = elem;
		*curr = elem;
	}
	else
	{
		(*curr)->next = elem;
		*curr = (*curr)->next;
	}
}
