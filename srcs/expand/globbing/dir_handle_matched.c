/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_handle_matched.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 17:20:49 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/07 17:21:47 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_matching.h"
#include "dir_explorer.h"

static int		handle_next(t_mtok *tok, t_entry **matched, t_entry *dats)
{
	t_entry		*e[2];
	t_entry		*t;
	t_entry		*ttt;
	t_mtok		*next;
	int			ret;

	e[0] = NULL;
	mtok_until_str(tok->next, "/", &next);
	e[1] = dats;
	while (e[1] != NULL)
	{
		dir_explore(e[1]->path, &t);
		t = ent_matching(tok->next, t);
		if (next == NULL || (ret = handle_matched(next, &ttt, t)) != 0)
		{
			if (e[0] == NULL)
				e[0] = (next != NULL) ? ttt : t;
			else
				ent_last(e[0])->next = (next != NULL) ? ttt : t;
		}
		e[1] = e[1]->next;
	}
	mtok_last(tok)->next = next;
	*matched = e[0];
	return (*matched != NULL);
}

int				handle_matched(t_mtok *tok, t_entry **matched, t_entry *dats)
{
	int			ret;

	if (dats == NULL)
		return (0);
	else if (tok == NULL)
	{
		*matched = dats;
		return (1);
	}
	if ((dats = ent_dirs(dats)) == NULL)
		return (0);
	if (tok->next == NULL)
	{
		if ((ret = ent_addslash(dats)) == -1)
			return (-1);
		else if (ret == 0)
			return (0);
		*matched = dats;
		return (1);
	}
	return (handle_next(tok, matched, dats));
}
