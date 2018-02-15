/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_setenv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:25:12 by vbastion          #+#    #+#             */
/*   Updated: 2017/12/15 16:30:33 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int			ft_setenv(char **args, t_environ *env)
{
	t_kvp	*kvp;
	int		pos;
	char	*strs[2];

	while (*args != NULL)
	{
		if ((pos = ft_strindex(*args, '=')) == -1)
		{
			ft_putstr_fd(SH_EWFMT, STDERR_FILENO);
			ft_putendl_fd(*args, STDERR_FILENO);
		}
		else if ((kvp = ft_env_nget(env->env, *args, pos)) == NULL)
		{
			strs[0] = ft_strndup(*args, pos);
			strs[1] = ft_strdup(*args + pos + 1);
			ft_env_insert(&env->env, strs[0], strs[1]);
		}
		else
		{
			strs[0] = kvp->value;
			kvp->value = ft_strdup(*args + pos + 1);
			ft_strdel(strs);
		}
		args++;
	}
	return (1);
}
