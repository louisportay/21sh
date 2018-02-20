/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:52:16 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/15 14:30:29 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char					*env_path_get(char *exe, char **pathes)
{
	static char			buffer[PATH_MAX + 1];
	size_t				i;

	if (pathes == NULL)
		return (NULL);
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

int						ctx_path(char *exe, t_ctx *ctx, char **path)
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
	{
	}
	if (*path != NULL)
	{
		ft_hashset_add(ctx->hash, exe, (void *)*path);
		return (1);
	}
	return (0);
}

int						loc_path(char *exe, char **env, char **path)
{
	char				*lpath;
	char				**pathes;

	lpath = ft_astr_getval(env, "PATH");
	if (lpath == NULL)
		return (0);
	if ((pathes = ft_strsplit(lpath, ':')) == NULL)
		return (0);
	*path = env_path_get(exe, pathes);
	ft_astr_clear(&pathes);
	return (*path != NULL);
}

int						get_path(char *exe, char **env, char **path,
									int locpath)
{
	if (locpath)
		return (loc_path(exe, env, path));
	return (ctx_path(exe, get_ctxaddr(NULL), path));
}
