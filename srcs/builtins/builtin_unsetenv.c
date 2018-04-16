/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 17:22:35 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/31 15:56:04 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	lrm(t_ctx *ctx, char *str)
{
	int		i;
	int		j;
	char	*s;

	i = ft_strlen(str);
	if ((j = ft_astr_getkey(ctx->environ, str, i)) != -1)
	{
		if (ft_strcmp(str, "PATH") == 0)
			path_reset(ctx, 0);
		s = ft_astr_remove_at(&ctx->environ, j);
		ft_strdel(&s);
	}
}

static int	ladd_err(char *av, char *name)
{
	ft_dprintf(STDERR_FILENO, "42sh: %s: %s: not a valid identifier\n",
				name, av);
	return (1);
}

int			ft_rmenv(t_proc *p, t_ctx *ctx, char *name)
{
	int		i;
	int		ret;

	p->type = BUILTIN;
	i = 1;
	ret = 0;
	while (p->argv[i] != NULL)
	{
		if (is_identifier(p->argv[i]))
			lrm(ctx, p->argv[i]);
		else
			ret |= ladd_err(p->argv[i], name);
		i++;
	}
	return (ret);
}

int			ft_unsetenv(t_proc *p, t_ctx *ctx)
{
	return (ft_rmenv(p, ctx, "unsetenv"));
}

int			ft_unset(t_proc *p, t_ctx *ctx)
{
	return (ft_rmenv(p, ctx, "unset"));
}
