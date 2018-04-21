/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtok_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 15:44:58 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/20 14:35:50 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

int				mtok_insert(t_mtok **head, t_mtok **curr, t_mtok *tmp)
{
	if (*head == NULL)
	{
		*head = tmp;
	}
	else
		(*curr)->next = tmp;
	*curr = mtok_last(tmp);
	return (1);
}

t_mtok			*mtok_last(t_mtok *last)
{
	if (last == NULL)
		return (NULL);
	if (last->next == NULL)
		return (last);
	while (last->next != NULL)
		last = last->next;
	return (last);
}
