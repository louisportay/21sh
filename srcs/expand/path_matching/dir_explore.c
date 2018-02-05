/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_explore.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:42:57 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/05 18:56:44 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./dir_explorer.h"
#include "./pattern_matching.h"

int				dir_explore(char *path, t_entry **ret)
{
	t_entry		*ent[3];
	DIR			*pdir;
	t_dir		*dir;

	if (access(path, X_OK | R_OK) == -1)
		return (0);
	if ((pdir = opendir(path)) == NULL)
		return (-1);
	ent[0] = NULL;
	ent[1] = NULL;
	while ((dir = readdir(pdir)) != NULL)
	{
		if ((ent[2] = ent_create(path, dir->d_name)) == NULL)
		{
			ent_clear(ent);
			return (-1);
		}
		ent_insert(ent, ent + 1, ent[2]);
	}
	closedir(pdir);
	*ret = ent[0];
	return (1);
}
