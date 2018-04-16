/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_fromcache.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 17:06:04 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/01 17:06:18 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

char					*path_fromcache(char *exe, t_ctx *ctx)
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
