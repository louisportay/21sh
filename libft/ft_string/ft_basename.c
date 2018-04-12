/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basename.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 09:43:57 by lportay           #+#    #+#             */
/*   Updated: 2018/04/11 15:18:24 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

/*
** Return the basename of a 'path'
** e.g. "/users/louisportay/Documents/somefile" --> "somefile"
**
** pass those tests with success
**
** printf("%s		%s\n", ft_basename(NULL), basename(NULL));
** printf("%s		%s\n", ft_basename("."), basename("."));
** printf("%s		%s\n", ft_basename(".."), basename(".."));
** printf("%s		%s\n", ft_basename("/"), basename("/"));
** printf("%s		%s\n", ft_basename("//////////"), basename("////////////"));
** printf("%s		%s\n", ft_basename("aaaaaaaaaaa"), basename("aaaaaaaaaaa"));
** printf("%s		%s\n", ft_basename("../aaaaaaa/.." ),
** basename("../aaaaaaa/.."));
** printf("%s		%s\n", ft_basename( "/a/b/c"     ), basename("/a/b/c"));
** printf("%s		%s\n", ft_basename( "//a/b"      ), basename("//a/b"));
** printf("%s		%s\n", ft_basename( "///a/b/c"   ), basename("///a/b/c"));
** printf("%s		%s\n", ft_basename( "a/b///c"      ), basename("a/b///c"));
** printf("%s		%s\n", ft_basename( "/aaaaaaaaa///bbbbb"    ),
** basename("/aaaaaaaaa///bbbbb"));
** printf("%s		%s\n", ft_basename( "aaaaaaaaa///bbbbb"    ),
** basename("aaaaaaaaa///bbbbb"));
** printf("%s		%s\n", ft_basename( "a/b"      ), basename("a/b"));
** printf("%s		%s\n", ft_basename( "aaaaaaaa/"), basename("aaaaaaaa/"));
** printf("%s		%s\n", ft_basename( "../aaaaaaaa/../"),
** basename("../aaaaaaaa/../"));
** printf("%s	%s\n", ft_basename( "/a/b/c/"    ), basename("/a/b/c/"));
** printf("%s	%s\n", ft_basename( "a/b/c/"     ), basename("a/b/c/"));
** printf("%s	%s\n", ft_basename( "///a/b/ci/" ), basename("///a/b/ci/"));
** printf("%s	%s\n", ft_basename( "///a/b//ci/" ), basename("///a/b//ci/"));
** printf("%s	%s\n", ft_basename( "///a/b/ci//" ), basename("///a/b/ci//"));
** printf("%s	%s\n", ft_basename( "///a/b//ci//" ), basename("///a/b//ci//"));
** printf("%s	%s\n", ft_basename( "///a/b/ci///" ), basename("///a/b/ci///"));
** printf("%s%s\n", ft_basename( "///a/b//ci///" ), basename("///a/b//ci///"));
** printf("%s	%s\n", ft_basename( "a/b/ci///" ), basename("a/b/ci///"));
** printf("%s	%s\n", ft_basename( "a/b//ci///" ), basename("a/b//ci///"));
** printf("%s	%s\n", ft_basename( "/aaaaaaaaa/" ), basename("/aaaaaaaaa/"));
** printf("%s%s\n", ft_basename( "/aaaaaaaaa///"), basename("/aaaaaaaaa///"));
** printf("%s	%s\n", ft_basename( "aaaaaaaaa///"), basename("aaaaaaaaa///"));
** printf("%s	%s\n", ft_basename( "///a///" ), basename("///a///"));
** printf("%s	%s\n", ft_basename( "a///" ), basename("a///"));
** printf("%s	%s\n", ft_basename( "/a///" ), basename("/a///"));
** printf("%s	%s\n", ft_basename( "a/b/"      ), basename("a/b/"));
*/

static char	*craft_basename(char *begin, int len)
{
	char *s;

	if (!(s = ft_strnew(len)))
		return (NULL);
	ft_memcpy(s, begin, len);
	return (s);
}

static char	*path_with_final_slash(char *path, char *first_char)
{
	int		slashes;

	slashes = 0;
	while (*first_char == '/')
	{
		first_char--;
		slashes++;
	}
	while (*first_char != '/' && first_char != path)
		first_char--;
	if (first_char == path && *first_char != '/')
		return (craft_basename(path, ft_strlen(path) - slashes));
	first_char++;
	return (craft_basename(first_char, ft_strlen(first_char) - slashes));
}

char		*ft_basename(char *path)
{
	char	*first_char;

	if (!path)
		return (ft_strdup("."));
	else if (!ft_strcmp(path, ".") || !ft_strcmp(path, "..") ||
			!ft_strcmp(path, "/") || !ft_strchr(path, '/'))
		return (ft_strdup(path));
	else if (ft_stroccur(path, '/') == ft_strlen(path))
		return (ft_strdup("/"));

	first_char = ft_strrchr(path, '/');
	if (*(first_char + 1) == '\0')
		return (path_with_final_slash(path, first_char));
	else
		first_char++;
	return (craft_basename(first_char, ft_strlen(first_char)));
}
