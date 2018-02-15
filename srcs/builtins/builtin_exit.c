/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 11:03:06 by vbastion          #+#    #+#             */
/*   Updated: 2017/12/14 20:13:44 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int			ft_err(char *str, char *err, int code)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putendl_fd(err, STDERR_FILENO);
	return (code);
}

# define MSH_EXIT ("exit")

# define MSH_ENUM ("Badly formed number.\n")
# define MSH_ESYNTAX ("Expression Syntax.\n")

int				ft_exit(char **args)
{
	if (*args == NULL)
		exit(0);
	if (ft_isnumber(*args) == 0)
		return (ft_err(MSH_EXIT, MSH_ENUM, 1));
	if (ft_astr_len(args) > 1)
		return (ft_err(MSH_EXIT, MSH_ESYNTAX, 1));
	exit((u_char)ft_atoi(*args));
	return (0);
}
