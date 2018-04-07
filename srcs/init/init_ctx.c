/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ctx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 19:37:06 by lportay           #+#    #+#             */
/*   Updated: 2018/04/07 20:39:33 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** mettre les variables dans l'ordre dans lequel elles ont ete declarees
** (les declarer dans un ordre logique)
*/

static void	init_linevar(t_ctx *ctx)
{
	ctx->cur_line = NULL;
	ctx->yank = NULL;
	ctx->line.line = NULL;
	ctx->line.lastline = NULL;
	ctx->line.linestate = NULL;
	ctx->line.eohdoc = NULL;
}

static void	init_parameters(t_ctx *ctx)
{
	ctx->emacs_mode = 1;
	ctx->line_edition = 1;
	ctx->config_file = 1;
	ctx->history = 1;
	ctx->job_control = 1;
}

void		init_ctx(t_ctx *ctx, char **av, char **environ)
{
	ctx->av = av;
	init_linevar(ctx);
	init_parameters(ctx);
	ctx->hist.list = ft_dlstnew("HEAD", 4);
	ctx->hist.index = 1;
	ctx->std_fd[0] = dup2(STDIN_FILENO, 10);
	ctx->std_fd[1] = dup2(STDOUT_FILENO, 11);
	ctx->std_fd[2] = dup2(STDERR_FILENO, 12);
	if (ctx->std_fd[0] != 10 || ctx->std_fd[1] != 11 || ctx->std_fd[2] != 12)
		exit(-1);
	ctx->istty = isatty(STDIN_FILENO);
	if (!ctx->istty || ioctl(STDIN_FILENO, TIOCGWINSZ, &ctx->ws) == -1)
		ctx->line_edition = 0;
	ctx->environ = ft_astr_dup(environ);
	ctx->hash = hash_create(HASH_SIZE, HASH_PRIME);
	ctx->ret_tcget = tcgetattr(STDIN_FILENO, &ctx->oldtios);
	ft_memcpy(&ctx->tios, &ctx->oldtios, sizeof(struct termios));
	create_locals(&ctx->locals);
	ctx->builtins = getbuiltins();
}
