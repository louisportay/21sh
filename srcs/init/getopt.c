/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getopt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 10:13:06 by lportay           #+#    #+#             */
/*   Updated: 2018/04/21 12:49:07 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	c_opt(t_ctx *ctx, char **av)
{
	t_dlist *l_av;

	if (av[1] == NULL)
		fatal_err(BADOPT_C, ctx);
	ctx->path = getpath(ctx->environ);
	l_av = dlst_from_str(av[1]);
	if (ft_dlstnewaddend(l_av, "\n", 1, &ft_dlstnew) == 1)
		fatal_err(NOMEM, get_ctxaddr());
	exec_loop(l_av);
	ft_dlstdel(&l_av, &delvoid);
	ctx->istty = 0;
	wrap_exit(EXIT_SUCCESS, ctx);
}

void		get_shell_opt(t_ctx *ctx, char **av)
{
	while (*av)
	{
		if (!ft_strcmp(*av, "--norc"))
			ctx->config_file = 0;
		else if (!ft_strcmp(*av, "--noediting"))
			ctx->line_edition = 0;
		else if (!ft_strcmp(*av, "-c"))
			c_opt(ctx, av);
		else if (!ft_strcmp(*av, "-h"))
		{
			ft_printf("%s%s%s", HELP1, HELP2, HELP3);
			ctx->istty = 0;
			wrap_exit(EXIT_SUCCESS, ctx);
		}
		av++;
	}
}
