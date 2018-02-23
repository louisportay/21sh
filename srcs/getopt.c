/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getopt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 10:13:06 by lportay           #+#    #+#             */
/*   Updated: 2018/02/23 16:48:08 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		get_shell_opt(t_ctx *ctx, char **av)
{
	while (*av)
	{
		if (!ft_strcmp(*av, "--norc"))
			ctx->config_file = 0;
		else if (!ft_strcmp(*av, "--rawline"))
			ctx->line_edition = 0;
		else if (!ft_strcmp(*av, "--nohist"))
			ctx->history = 0;
		else if (!ft_strcmp(*av, "-f"))
		{
			if (av[1] == NULL)
				fatal_err(BADOPT_F, ctx);
			ctx->fd = open(av[1], O_RDONLY);
			ctx->istty = isatty(ctx->fd);
			break ;
		}
		else if (!ft_strcmp(*av, "-c"))
		{
			t_dlist *l_av;

			if (av[1] == NULL)
				fatal_err(BADOPT_C, ctx);
			l_av = str_to_dlst(av[1]);
			ft_dlstaddend(l_av, ft_dlstnew("\n", 1));
			exec_loop(l_av);
			ft_dlstdel(&l_av, &delvoid);
			wrap_exit(0, ctx);
		}
		else if (!ft_strcmp(*av, "-h"))
		{
			ft_putstr(HELP1 HELP2 HELP3 HELP4 HELP5);
			wrap_exit(0, ctx);
		}

		av++;
	}
}
