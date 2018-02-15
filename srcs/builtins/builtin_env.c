/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 12:49:48 by vbastion          #+#    #+#             */
/*   Updated: 2017/12/15 15:13:41 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char		*l_getpath(char *raw, t_kvp *env, char **path)
{
	(void)raw;
	(void)env;
	(void)path;
	return (NULL);
}

int             l_exec(char **argv, t_kvp *env, t_environ *envi)
{
    pid_t       pid;
    char        *path;
    int         status;

	if (*argv == NULL)
		return (0);
    if (builtin_assert(argv, envi))
        return (1);
    if (l_getpath(*argv, envi->env, &path) == 0)
        return (0);
    if ((pid = fork()) == -1)
    {
        ft_putstr_fd("Could not fork.\n", STDERR_FILENO);
        return (0);
    }
    if (pid == 0)
	{
		char **astrenv = ft_env_toastr(env);
		execve(path, argv, astrenv);
	}
    else
        waitpid(pid, &status, 0);
    return (1);
}

int				ft_env(char **args, t_environ *env)
{
	t_kvp		*envdup;

	if (*args == NULL)
		ft_printenv(NULL, env);
	else if (ft_strcmp("-i", *args) == 0)
		l_exec(args + 1, NULL, env);
	else if (ft_strcmp("-u", *args) == 0)
	{
		if (args[1] == NULL)
			return (1);
		envdup = ft_env_dup_but(env->env, args[1]);
		l_exec(args + 2, envdup, env);
	}
	else
	{
		envdup = ft_env_dup(env->env);
		l_exec(args + 1, envdup, env);
	}
	return (1);
}
