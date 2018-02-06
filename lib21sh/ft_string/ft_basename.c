/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basename.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 09:43:57 by lportay           #+#    #+#             */
/*   Updated: 2018/02/06 16:02:43 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
** Return the basename of a 'path'
** e.g. "/users/louisportay/Documents/somefile" --> "somefile"
*/

char	*ft_basename(char *path)
{
	char *begin;
	char *end;

	if (!path)
		return (ft_strdup("."));
	else if (!ft_strcmp(path, ".") || !ft_strcmp(path, "..") ||
			!ft_strcmp(path, "/") || !ft_strchr(path, '/'))
		return (ft_strdup(path));
	else if (ft_stroccur(path, '/') == ft_strlen(path))
		return (ft_strdup("/"));
	begin = path;
	while (*path)
		path++;
	path--;
	while (*path == '/')
		path--;
	end = path + 1;
	while (*path != '/' && path != begin)
		path--;	
	if (path != begin)
		path++;
	if (!(begin = (char *)malloc(sizeof(char) * (end - path + 1))))
		return (NULL);
	ft_memcpy(begin, path, (end - path));
	begin[end - path] = '\0';
	return (begin);
}
