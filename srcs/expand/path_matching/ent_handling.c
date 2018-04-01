/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 18:28:52 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/01 17:22:36 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dir_explorer.h"
#include "pattern_matching.h"

t_entry			*ent_create(char *path, char *name)
{
	t_entry		*ret;

	if ((ret = (t_entry *)ft_memalloc(sizeof(t_entry))) == NULL)
		return (NULL);
	ret->name = ft_strdup(name);
	ret->path = path == NULL ? ft_strdup(name) : ft_strjoinc(path, name, '/');
	if (ret->name == NULL || ret->path == NULL)
	{
		ft_strdel(&ret->name);
		ft_strdel(&ret->path);
		ft_memdel((void **)&ret);
		return (NULL);
	}
	return (ret);
}

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
	else
		(*curr)->next = tmp;
	*curr = ent_last(tmp);
}

void			ent_clear(t_entry **ent)
{
	t_entry		*e;
	t_entry		*t;

	if (ent == NULL)
		return ;
	e = *ent;
	*ent = NULL;
	while (e != NULL)
	{
		t = e;
		e = e->next;
		ft_strdel(&t->name);
		ft_strdel(&t->path);
		ft_memdel((void **)&t);
	}
}

char			*ent_cat(t_entry *entries)
{
	t_qbuf		*buf;

	if (entries == NULL)
		return (NULL);
	buf = qbuf_new(128);
	while (entries != NULL)
	{
		qbuf_add(buf, entries->path);
		if (entries->next != NULL)
			qbuf_addc(buf, ' ');
		entries = entries->next;
	}
	return (qbuf_del(&buf));
}
