/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_unsetenv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 17:22:35 by vbastion          #+#    #+#             */
/*   Updated: 2017/12/14 20:15:07 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int				ft_unsetenv(char **args, t_environ *env)
{
	while (*args != NULL)
	{
		if (ft_env_pop(&env->env, *args) == 0)
		{
			ft_putstr_fd(SH_ENKEY, STDERR_FILENO);
			ft_putendl_fd(*args, STDERR_FILENO);
		}
		args++;
	}
	return (0);
}
