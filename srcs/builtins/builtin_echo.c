/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:18:08 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/15 18:33:23 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int				ft_echo(char **args, t_ctx *ctx)
{
	size_t		i;
	int			nl;

	(void)ctx;
	if (*args == NULL)
		return (write(STDOUT_FILENO, "\n", 1));
	nl = (ft_strcmp("-n", *args) != 0);
	args += nl ? 0 : 1;
	i = 0;
	while (args[i] != NULL)
	{
		ft_putstr(args[i]);
		i++;
		if (args[i] != NULL)
			write(STDOUT_FILENO, " ", 1);
	}
	if (nl)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
