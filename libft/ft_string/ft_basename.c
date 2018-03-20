/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basename.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 09:43:57 by lportay           #+#    #+#             */
/*   Updated: 2018/03/19 15:55:50 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
** Return the basename of a 'path'
** e.g. "/users/louisportay/Documents/somefile" --> "somefile"
*/

char	*ft_basename(char *path)
{
	char *s;

	if (!path)
		return (ft_strdup("."));
	else if (!ft_strcmp(path, ".") || !ft_strcmp(path, "..") ||
			!ft_strcmp(path, "/") || !ft_strchr(path, '/'))
		return (ft_strdup(path));
	else if (ft_stroccur(path, '/') == ft_strlen(path))
		return (ft_strdup("/"));
	path = ft_strrchr(path, '/') + 1;
	if (!(s = ft_strnew(ft_strlen(path))))
		return (NULL);
	ft_memcpy(s, path, ft_strlen(path) + 1);
	return (s);
}
