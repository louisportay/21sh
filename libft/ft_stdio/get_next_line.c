/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 11:24:47 by lportay           #+#    #+#             */
/*   Updated: 2018/02/11 15:25:16 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdio.h"

static void	join_gnl(char **rest, char *buf)
{
	char *old_rest_to_free;

	if (!(*rest))
		*rest = ft_strdup(buf);
	else
	{
		old_rest_to_free = *rest;
		*rest = ft_strjoin(*rest, buf);
		ft_strdel(&old_rest_to_free);
	}
}

static int	find_nl(char *buf, char **rest, char **nl_ptr, int fd)
{
	int ret;

	ft_bzero(buf, BUFF_SIZE + 1);
	if ((ret = read(fd, buf, BUFF_SIZE)) == -1)
		return (ret);
	while (!(*nl_ptr = ft_strchr(buf, '\n')))
	{
		if (ret == 0)
			return ((!(*rest) || ft_strlen(*rest) == 0) ? 0 : 1);
		join_gnl(rest, buf);
		ft_bzero(buf, BUFF_SIZE);
		if ((ret = read(fd, buf, BUFF_SIZE)) == -1)
			return (ret);
	}
	return (2);
}

static void	gnl_end(char *buf, char **rest, char **line, char **nl_ptr)
{
	**nl_ptr = '\0';
	join_gnl(rest, buf);
	*line = *rest;
	*rest = ft_strdup(*nl_ptr + 1);
	if (rest && (ft_strlen(*rest) == 0))
		ft_strdel(rest);
}

/*
** la fonction écrit dans 'line' la ligne lue depuis le 'fd' indiqué, puis lit
** une nouvelle ligne à chaque appel de la fonction. renvoie 1 quand elle a lu
** une ligne, 0 quand le fichier est fini, -1 quand une erreur est survenue.
*/

int			get_next_line(const int fd, char **line)
{
	static char	*rest = NULL;
	char		*nl_ptr;
	char		buf[BUFF_SIZE + 1];
	int			ret;

	if (BUFF_SIZE <= 0 || fd < 0)
		return (-1);
	if (rest != NULL && (nl_ptr = ft_strchr(rest, '\n')) != NULL)
	{
		*nl_ptr = '\0';
		*line = rest;
		rest = ft_strdup(nl_ptr + 1);
		return (1);
	}
	if ((ret = find_nl(buf, &rest, &nl_ptr, fd)) == -1 || ret == 0 || ret == 1)
	{
		if (ret == -1)
			return (ret);
		*line = rest;
		rest = NULL;
		return (ret);
	}
	gnl_end(buf, &rest, line, &nl_ptr);
	return (1);
}
