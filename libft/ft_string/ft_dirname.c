/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dirname.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 09:45:53 by lportay           #+#    #+#             */
/*   Updated: 2018/02/06 16:02:43 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
** Return the dirname of a 'path'
** e.g. "/some/really/fancy/path" --> "/some/really/fancy"
*/

char	*ft_dirname(char *path)
{
	char *tmp;
	char *dirname;
	unsigned len;

	if (!path || ft_stroccur(path, '.') == (len = ft_strlen(path)) ||
		!(tmp = ft_strchr(path, '/')) || (*(tmp + 1) == '\0' && len != 1))
		return (ft_strdup("."));
	else if (ft_stroccur(path, '/') == len)
		return (ft_strdup("/"));
	tmp = path;
	while (*path)
		path++;
	path--;
	while (*path == '/')
		path--;
	while (*path != '/')
		path--;
	if (path == tmp)
		return (ft_strdup("/"));
	len = (path - tmp);
	if (!(dirname = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_memcpy(dirname, tmp, len);
	dirname[len] = '\0';
	return (dirname);
}
