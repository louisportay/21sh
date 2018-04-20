/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_lifecycle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 15:18:26 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/20 14:17:07 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

t_entry			*ent_create(char *path, char *name)
{
	t_entry		*ret;

	if ((ret = (t_entry *)ft_pmemalloc(sizeof(t_entry),
										&on_emem, NOMEM)) == NULL)
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

void			ent_free(t_entry **ent)
{
	ft_strdel(&((*ent)->name));
	ft_strdel(&((*ent)->path));
	ft_memdel((void **)ent);
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
		ent_free(&t);
	}
}
