/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 18:28:52 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/20 15:59:15 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

t_entry			*ent_last(t_entry *ent)
{
	if (ent == NULL)
		return (NULL);
	while (ent->next != NULL)
		ent = ent->next;
	return (ent);
}

void			ent_insert(t_entry **head, t_entry **curr, t_entry *tmp)
{
	if (*head == NULL)
		*head = tmp;
	else if (*curr == NULL)
	{
		ent_last(*head)->next = tmp;
		*curr = ent_last(tmp);
	}
	else
		(*curr)->next = tmp;
	*curr = ent_last(tmp);
}

void			ent_insert_one(t_entry *entries[2], t_entry *elem)
{
	if (entries[0] == NULL)
		entries[0] = elem;
	else
		entries[1]->next = elem;
	entries[1] = elem;
}

char			*ent_cat(t_entry *entries, int append)
{
	t_qbuf		*buf;

	if (entries == NULL)
		return (NULL);
	buf = qbuf_new(128);
	while (entries != NULL)
	{
		qbuf_add(buf, entries->path);
		if (append)
			qbuf_addc(buf, '/');
		if (entries->next != NULL)
			qbuf_addc(buf, ' ');
		entries = entries->next;
	}
	return (qbuf_del(&buf));
}
