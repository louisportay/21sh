/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dirname.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 20:08:27 by lportay           #+#    #+#             */
/*   Updated: 2018/04/11 13:53:58 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_dirname(char *path)
{
	char	*last_char;
	char	*dirname;

	if (!path || !ft_strchr(path, '/'))
		return (ft_strdup("."));
	else if (ft_strlen(path) == ft_stroccur(path, '/'))
		return (ft_strdup("/"));
	last_char = path + ft_strlen(path) - 1;
	while (*last_char == '/')
		last_char--;
	while (*last_char != '/' && last_char != path)
		last_char--;
	if (last_char == path)
		return (*last_char == '/' ? ft_strdup("/") : ft_strdup("."));
	while (*last_char == '/' && last_char != path)
		last_char--;
	if (last_char == path && *last_char == '/')
		return (ft_strdup("/"));
	last_char++;
	if ((dirname = ft_strnew(last_char - path)) == NULL)
			return (NULL);
	ft_memcpy(dirname, path, last_char - path);
	return (dirname);
}
