/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:52:16 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/12 14:53:11 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char					*env_path_get(char *exe, char **pathes)
{
	static char			buffer[PATH_MAX + 1];
	size_t				i;

	i = 0;
	while (pathes[i] != NULL)
	{
		ft_bzero(buffer, PATH_MAX + 1);
		ft_strcat(buffer, pathes[i]);
		ft_strcat(buffer, "/");
		ft_strcat(buffer, exe);
		if (access(buffer, X_OK) == 0)
			return (buffer);
		i++;
	}
	return (NULL);
}

int						get_path(char *exe, t_ctx *ctx, char **path)
{
	t_hash_entry		*e;

	*path = NULL;
	if (ft_strindex(exe, '/') != -1)
	{
		if (access(exe, X_OK) == 0)
		{
			*path = exe;
			return (1);
		}
		return (0);
	}
	else if ((e = ft_hashset_lookup(ctx->hash, exe)) != NULL)
		*path = (char *)e->content;
	else if ((*path = env_path_get(exe, ctx->path)) != NULL)
		;
	if (*path != NULL)
	{
		ft_hashset_add(ctx->hash, exe, (void *)*path);
		return (1);
	}
	return (0);
}
