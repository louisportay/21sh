/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 17:54:04 by lportay           #+#    #+#             */
/*   Updated: 2017/08/23 18:00:53 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	del_env(char *tmp, char **tmp_env, char ***env)
{
	size_t	cells;
	char	**new_env;

	cells = 0;
	ft_strrep(&tmp, *--tmp_env);
	tmp_env = *env;
	while (*tmp_env++)
		cells++;
	if (!(new_env = (char **)malloc(sizeof(char *) * cells)))
		return (-1);
	tmp_env = new_env;
	while (**env)
	{
		if (ft_strcmp(**env, tmp) != 0)
			*tmp_env++ = **env;
		(*env)++;
	}
	*tmp_env = NULL;
	ft_strdel(&tmp);
	free(*env - cells);
	*env = new_env;
	return (0);
}

int			ft_unsetenv(const char *name, char ***env)
{
	char	*tmp;
	char	**tmp_env;
	int		len;

	if (!name)
		return (-1);
	tmp = ft_strjoin(name, "=");
	tmp_env = *env;
	len = ft_strlen(tmp);
	while (*tmp_env)
		if (ft_strncmp(*tmp_env++, tmp, len) == 0)
			return (del_env(tmp, tmp_env, env));
	ft_strdel(&tmp);
	return (0);
}
