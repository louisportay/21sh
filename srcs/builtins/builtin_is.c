/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_is.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 18:08:37 by vbastion          #+#    #+#             */
/*   Updated: 2017/12/15 14:39:40 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int			builtin_assert(char **argv, t_environ *env)
{
	if (ft_strcmp(*argv, SH_ECHO) == 0)
		ft_echo(argv + 1);
	else if (ft_strcmp(*argv, SH_EXIT) == 0)
		ft_exit(argv + 1);
	else if (ft_strcmp(*argv, SH_ENV_) == 0)
		ft_env(argv + 1, env);
	else if (ft_strcmp(*argv, SH_PENV) == 0)
		ft_printenv(argv + 1, env);
	else if (ft_strcmp(*argv, SH_CD__) == 0)
		ft_cd(argv + 1, env);
	else if (ft_strcmp(*argv, SH_SETE) == 0)
		ft_setenv(argv + 1, env);
	else if (ft_strcmp(*argv, SH_UNSE) == 0)
		ft_unsetenv(argv + 1, env);
	else
		return (0);
	return (1);
}
