/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 11:37:11 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/18 19:23:12 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int			ft_err(char *str, char *err, int code)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(err, STDERR_FILENO);
	return (code);
}

static int			ft_puterror(char *str, int code)
{
	ft_putstr_fd(str, STDERR_FILENO);
	return (code);
}

static int			l_cd(char *path, t_environ *env)
{
	char			cwd[MAXPATHLEN];
	struct stat		stats;

	getcwd(cwd, MAXPATHLEN);
	if (chdir(path) != 0)
	{
		if (stat(path, &stats) == -1)
			return (ft_err(path, SH_ENOFOD, 0));
		else if (access(path, X_OK) == -1)
			return (ft_err(path, SH_ERIGHT, 0));
	}
	ft_env_safe_insert(&env->env, ENV_OLDPWD, ft_strdup(cwd));
	getcwd(cwd, MAXPATHLEN);
	ft_env_safe_insert(&env->env, ENV_PWD, ft_strdup(cwd));
	return (1);
}

static int			l_cd_tar(char *key, char *errmsg, t_environ *env)
{
	char			*str;

	if ((str = ft_env_get_value(env->env, key)) == NULL)
		return (ft_puterror(errmsg, 0));
	return (l_cd(str, env));
}

int					ft_cd(char **args, t_environ *env)
{
	if (ft_astr_len(args) > 1)
		return (ft_puterror(SH_EARGTO, 0));
	if (*args == NULL)
		return (l_cd_tar(ENV_HOME, SH_ENOHOM, env));
	else if (ft_strcmp("-", *args) == 0)
		return (l_cd_tar(ENV_OLDPWD, SH_ENOOPW, env));
	return (l_cd(*args, env));
}
