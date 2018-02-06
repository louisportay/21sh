/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __getpath__.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 12:54:23 by lportay           #+#    #+#             */
/*   Updated: 2018/02/06 16:02:43 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
** pathlist is the string formatted as in the PATH variable `path1:path2:path3`
** and exec is the name of the executable we're looking the fullpath
** If the right path is found, the malloc'ed string is returned (NULL otherwise)
*/

char	*getpath(char *pathlist, char *exec)
{
	char	**paths;
	char 	**addr;
	char	*tmp;

	if (!(paths = ft_strsplit(pathlist, ':')))
		return (NULL);
	addr = paths;
	while (*paths)
	{
		if (access(tmp = fullpath(*paths, exec), X_OK) == 0)
			break ;
		free(tmp);
		paths++;
	}
	if (!(*paths))
		tmp = NULL;
	del_array((void *)addr);
	free(addr);
	return (tmp);
}
