/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_explore.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 16:42:57 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/20 16:08:12 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

static DIR		*safe_opendir(char *path)
{
	struct stat	stats;

	if (path == NULL)
		return (NULL);
	else if (stat(path, &stats) == -1)
		return (NULL);
	else if (S_ISDIR(stats.st_mode) == 0)
		return (NULL);
	else if ((stats.st_mode & S_IRUSR) == 0)
		return (NULL);
	return (opendir(path));
}

int				dir_explore(char *path, t_entry **ret, int show_hidden)
{
	t_entry		*ent[3];
	DIR			*pdir;
	t_dir		*dir;
	int			curr;

	curr = (path == NULL);
	path = curr ? "." : path;
	if ((pdir = safe_opendir(path)) == NULL)
		return (-1);
	ent[0] = NULL;
	ent[1] = NULL;
	while ((dir = readdir(pdir)) != NULL)
	{
		if (show_hidden == 0 && dir->d_name[0] == '.')
			continue ;
		ent[2] = ent_create(curr ? NULL : path, dir->d_name);
		ent_insert(ent, ent + 1, ent[2]);
	}
	closedir(pdir);
	*ret = ent[0];
	return (1);
}
