/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getopt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 10:13:06 by lportay           #+#    #+#             */
/*   Updated: 2018/02/23 10:24:32 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	getopt_21sh(t_ctx *ctx, char **av)
{
	while (*av)
	{
		if (!ft_strcmp(*av, "--norc"))
			ctx->config_file = 0;
		else if (!ft_strcmp(*av, "--rawline"))
			ctx->line_edition = 0;
		else if (!ft_strcmp(*av, "--nohist"))
			ctx->history = 0;
		av++;
	}
}
