/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:52:16 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/13 11:50:13 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int				path_handle(char *path, t_proc *p, int hash)
{
	struct stat			stats;

	if (lstat(path, &stats) == -1)
	{
		p->type = hash ? EXNFOD : EXNFD;
		return (1);
	}
	else if (S_ISDIR(stats.st_mode))
	{
		p->type = EXDIR;
		return (1);
	}
	else if ((S_IXUSR & stats.st_mode) == 0)
	{
		p->type = EXPERM;
		return (1);
	}
	p->type = BINARY;
	return (0);
}

char					*env_path_get(char *exe, char **pathes)
{
	static char			buffer[PATH_MAX + 1];
	size_t				i;
	struct stat			stats;

	if (pathes == NULL)
		return (NULL);
	i = 0;
	while (pathes[i] != NULL)
	{
		if ((ft_strlen(pathes[i]) + ft_strlen(exe)) > PATH_MAX)
			return (NULL);
		ft_bzero(buffer, PATH_MAX + 1);
		ft_strcat(buffer, pathes[i]);
		ft_strcat(buffer, "/");
		ft_strcat(buffer, exe);
		if (stat(buffer, &stats) == -1)
			;
		else if (S_ISDIR(stats.st_mode))
			;
		else if (S_IXUSR & stats.st_mode)
			return (buffer);
		i++;
	}
	return (NULL);
}

static char				*path_fromctx(char *exe, t_ctx *ctx, t_proc *p)
{
	t_hentry			*e;
	char				*path;

	path = NULL;
	if ((e = hash_lookup(ctx->hash, exe)) != NULL)
	{
		if (path_handle((char *)e->content, p, 1))
		{
			if (p->type == EXNFOD)
				p->data.path = ft_strdup((char *)e->content);
			return (p->data.path);
		}
		if ((path = ft_strdup((char *)e->content)) == NULL)
			on_emem(NOMEM);
		return (path);
	}
	else
		return (path_fromcache(exe, ctx));
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
	if (p->argv[0][0] == '\0')
	{
		p->type = EXERR;
		return (NULL);
	}
	if (ft_strindex(p->argv[0], '/') != -1)
	{
		if (path_handle(p->argv[0], p, 0) != 0)
			return (NULL);
		if ((p->data.path = ft_strdup(p->argv[0])) == NULL)
			on_emem(NOMEM);
		return (p->data.path);
	}
	p->data.path = ((locpath == 0) ? path_fromctx(p->argv[0], ctx, p)
					: llocpath(p));
	if (p->type == EXNFOD)
		return (NULL);
	p->type = (p->data.path == NULL) ? EXNFD : BINARY;
	return (p->data.path);
}
