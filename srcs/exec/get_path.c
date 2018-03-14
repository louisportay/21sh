/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:52:16 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/14 17:16:52 by vbastion         ###   ########.fr       */
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
	t_hentry		*e;

	*path = NULL;
	if ((e = hash_lookup(ctx->hash, exe)) != NULL)
		*path = (char *)e->content;
	else
		*path = env_path_get(exe, ctx->path);
	if (*path != NULL)
	{
		hash_add(ctx->hash, exe, (void *)*path);
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

static char				*lnpath(char *exe, t_ctx *ctx)
{
	char				*dkey;
	char				*dpath;
	char				*path;

	if ((path = env_path_get(exe, ctx->path)) == NULL)
		return (NULL);
	if ((path = ft_strdup(path)) == NULL)
		on_emem(NOMEM);
	dkey = ft_strdup(exe);
	if ((dpath = ft_strdup(path)) == NULL || dkey == NULL)
	{
		ft_strdel(&dkey);
		ft_strdel(&dpath);
		on_emem(NOMEM);
		return (NULL);
	}
	hash_add(ctx->hash, dkey, dpath);
	return (path);
}

char					*path_fromctx(char *exe, t_ctx *ctx)
{
	t_hentry			*e;
	char				*path;

	path = NULL;
	if ((e = hash_lookup(ctx->hash, exe)) != NULL)
	{
		if ((path = ft_strdup((char *)e->content)) == NULL)
			on_emem(NOMEM);
		return (path);
	}
	else
		return (lnpath(exe, ctx));
}

static char				*llocpath(t_proc *p)
{
	char				*lpath;
	char				**pathes;
	char				*path;

	if ((lpath = ft_astr_getval(p->env, "PATH")) == NULL)
		return (NULL);
	if ((pathes = ft_strsplit(lpath, ':')) == NULL)
		return (NULL);
	if ((path = env_path_get(p->argv[0], pathes)) == NULL)
		return (NULL);
	ft_astr_clear(&pathes);
	if ((path = ft_strdup(path)) == NULL)
		on_emem(NOMEM);
	return (path);
}

char					*proc_path(t_proc *p, t_ctx *ctx, int locpath)
{
	char				*path;

	if (ft_strindex(p->argv[0], '/') != -1)
	{
		if (access(p->argv[0], X_OK) == 0)
		{
			if ((path = ft_strdup(p->argv[0])) == NULL)
				on_emem(NOMEM);
			return (path);
		}
		return (NULL);
	}
	return (locpath == 0 ? path_fromctx(p->argv[0], ctx) : llocpath(p));
}
