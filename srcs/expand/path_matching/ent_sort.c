/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 12:58:00 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/07 15:50:35 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dir_explorer.h"
#include "pattern_matching.h"

t_entry			*ent_dirs(t_entry *dats)
{
	t_entry		*ent[5];
	struct stat	stats;

	ent[0] = NULL;
	ent[2] = NULL;
	while (dats != NULL)
	{
		ent[4] = dats;
		dats = dats->next;
		ent[4]->next = NULL;
		stat(ent[4]->path, &stats);
		if (S_ISDIR(stats.st_mode))
			ent_insert(ent, ent + 1, ent[4]);
		else
			ent_insert(ent + 2, ent + 3, ent[4]);
	}
	ent_clear(ent + 2);
	return (ent[0]);
}

t_entry			*ent_matching(t_mtok *tok, t_entry *dats)
{
	t_entry		*matchies[5];

	if (tok == NULL)
		return (0);
	matchies[0] = NULL;
	matchies[2] = NULL;
	while (dats != NULL)
	{
		matchies[4] = dats;
		dats = dats->next;
		matchies[4]->next = NULL;
		if (ent_match(matchies[4]->name, tok))
			ent_insert(matchies, matchies + 1, matchies[4]);
		else
			ent_insert(matchies + 2, matchies + 3, matchies[4]);
	}
	ent_clear(matchies + 2);
	return (matchies[0]);
}

int				ent_addslash(t_entry *dats)
{
	char		*tmp;

	if (dats == NULL)
		return (0);
	while (dats != NULL)
	{
		tmp = dats->path;
		if ((dats->path = ft_strjoin(dats->path, "/")) == NULL)
		{
			ent_clear(&dats);
			return (-1);
		}
		ft_strdel(&tmp);
		dats = dats->next;
	}
	return (1);
}

void			ent_print(t_entry *ent, int lfmt)
{
	while (ent != NULL)
	{
		ft_putendl(lfmt ? ent->path : ent->name);
		ent = ent->next;
	}
}
