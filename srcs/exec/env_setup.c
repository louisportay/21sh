/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 17:17:41 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/31 14:44:15 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ.h"

int						env_setup(t_env *env, char **environ)
{
	char				*path;

	ft_bzero(env, sizeof(t_env));
	env->env = ft_env_copy(environ);
	if ((path = ft_env_get_value(env->env, "PATH")) != NULL)
	{
		if ((env->path = ft_strsplit(path, ':')) == NULL)
			return (0);
	}
	if (astr_rmdup(&env->path) == -1)
	{
		ft_env_clear(&env->env);
		return (-1);
	}
	env->hash = ft_hashset_create(HASH_SIZE, HASH_PRIME);
	return (1);
}

char					*env_path_get(char *exe, t_env *env)
{
	static char			buffer[PATH_MAX + 1];
	size_t				i;

	i = 0;
	while (env->path[i] != NULL)
	{
		ft_bzero(buffer, PATH_MAX + 1);
		ft_strcat(buffer, env->path[i]);
		ft_strcat(buffer, "/");
		ft_strcat(buffer, exe);
		if (access(buffer, X_OK) == 0)
			return (buffer);
		i++;
	}
	return (NULL);
}

int						get_path(char *exe, t_env *env, char **path)
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
	else if ((e = ft_hashset_lookup(env->hash, exe)) != NULL)
		*path = (char *)e->content;
	else if ((*path = env_path_get(exe, env)) != NULL)
		;
	if (*path != NULL)
	{
		ft_hashset_add(env->hash, exe, (void *)*path);
		return (1);
	}
	return (0);
}
