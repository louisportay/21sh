/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:31:13 by vbastion          #+#    #+#             */
/*   Updated: 2017/12/13 17:29:25 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_printenv(t_environ *env)
{
	ft_astr_foreach(env, &ft_putendl);
	return (0);
}

static int		append_vars(char ***args, t_environ *env)
{
	char		**curr;
	int			pos;
	int			id;
	int			changed;

	curr = *args;
	changed = 0;
	while (*curr != NULL && (pos = ft_strindex(*curr, '=')) != -1)
	{
		if ((id = ft_astr_nbeginswith(*env, *curr, pos)) != -1)
		{
			ft_strdel(*env + id);
			(*env)[id] = ft_strdup(*curr);
		}
		else
			ft_astr_append(env, *curr);
		changed = 1;
		curr++;
	}
	*args = curr;
	return (changed);
}

static int		tmp_env(char **args, t_environ *env)
{
	char		**tmp_environ;
	char		*path;
	int			ret;
	int			print;

	tmp_environ = ft_astr_dup(*env);
	print = append_vars(&args, &tmp_environ);
	if (*args != NULL)
	{
		if ((path = ft_get_path(tmp_environ, args[0])) != NULL)
			ret = ft_try_exec(path, args, tmp_environ);
		else
			ft_puterror(args[0], MSH_ECMD);
	}
	else if (print)
		ft_env(NULL, &tmp_environ);
	ft_astr_free(&tmp_environ);
	return (1);
}

int				ft_env(char **args, t_environ *env)
{
	if (args == NULL || *args == NULL)
		return (ft_printenv(*env));
	else
		return (tmp_env(args, env));
	return (0);
}
