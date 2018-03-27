/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getopt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 10:13:06 by lportay           #+#    #+#             */
/*   Updated: 2018/03/27 12:30:42 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	c_opt(t_ctx *ctx, char **av)
{
	t_dlist *l_av;

	if (av[1] == NULL)
		fatal_err(BADOPT_C, ctx);
	ctx->path = getpath(ctx->environ);
	l_av = dlst_from_str(av[1]);
	ft_dlstaddend(l_av, ft_dlstnew("\n", 1));
	exec_loop(l_av);
	ft_dlstdel(&l_av, &delvoid);
	ctx->istty = 0;
	wrap_exit(0, ctx);
}

static void	f_opt(t_ctx *ctx, char **av)
{
	if (av[1] == NULL)
		fatal_err(BADOPT_F, ctx);
	ctx->fd = open(av[1], O_RDONLY);
	ctx->istty = isatty(ctx->fd);
	ctx->line_edition = 0;
}

void		get_shell_opt(t_ctx *ctx, char **av)
{
	while (*av)
	{
		if (!ft_strcmp(*av, "--norc"))
			ctx->config_file = 0;
		else if (!ft_strcmp(*av, "--noediting"))
			ctx->line_edition = 0;
		else if (!ft_strcmp(*av, "-f"))
			return (f_opt(ctx, av));
		else if (!ft_strcmp(*av, "-c"))
			c_opt(ctx, av);
		else if (!ft_strcmp(*av, "-h"))
		{
			ft_printf("%s%s%s", HELP1, HELP2, HELP3);
			ctx->istty = 0;
			wrap_exit(0, ctx);
		}
		av++;
	}
}
