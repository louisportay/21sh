/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:03:14 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/15 19:15:36 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int				ft_printenv(char **args, t_ctx *ctx)
{
	int			i;
	char		*str;

	i = 0;
	if (args[i] == NULL)
	{
		while (ctx->environ[i] != NULL)
			printf("%s\n", ctx->environ[i++]);
	}
	else
	{
		while (args[i] != NULL)
		{
			if ((str = ft_astr_getval(ctx->environ, args[i])) != NULL)
				printf("%s\n", str);
			else
				dprintf(STDERR_FILENO, "No key '%s' in environ\n", args[i]);
			i++;
		}
	}
	return (0);
}
