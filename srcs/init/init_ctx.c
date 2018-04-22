/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ctx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 19:37:06 by lportay           #+#    #+#             */
/*   Updated: 2018/04/22 18:01:04 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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

static void	set_term_fd(t_ctx *ctx)
{
	ctx->std_fd[0] = dup2(STDIN_FILENO, TERM_FD_STDIN);
	ctx->std_fd[1] = dup2(STDOUT_FILENO, TERM_FD_STDOUT);
	ctx->std_fd[2] = dup2(STDERR_FILENO, TERM_FD_STDERR);
	if (ctx->std_fd[0] == -1 || ctx->std_fd[1] == -1 || ctx->std_fd[2] == -1)
	{
		ft_dprintf(STDERR_FILENO, "Could not save default FD\n");
		exit(-1);
	}
	if ((ctx->istty = isatty(STDIN_FILENO)))
	{
		ctx->term_fd = dup2(STDIN_FILENO, TERM_FD);
		return ;
	}
	else if (isatty(STDOUT_FILENO))
	{
		ctx->term_fd = dup2(STDOUT_FILENO, TERM_FD);
		return ;
	}
	else if (isatty(STDERR_FILENO))
	{
		ctx->term_fd = dup2(STDERR_FILENO, TERM_FD);
		return ;
	}
	ctx->istty = 0;
}

void		init_ctx(t_ctx *ctx, char **av, char **environ)
{
	ctx->av = av;
	ctx->ret_tcget = tcgetattr(STDIN_FILENO, &ctx->oldtios);
	init_linevar(ctx);
	init_parameters(ctx);
	if ((ctx->hist.list = ft_dlstnew("HEAD", 4)) == NULL)
		fatal_err(NOMEM, ctx);
	ctx->hist.index = 1;
	set_term_fd(ctx);
	if (!ctx->istty || ioctl(STDIN_FILENO, TIOCGWINSZ, &ctx->ws) == -1)
		ctx->line_edition = 0;
	if ((ctx->environ = ft_astr_dup(environ)) == NULL)
		fatal_err(NOMEM, ctx);
	ctx->hash = hash_create(HASH_SIZE, HASH_PRIME);
	ft_memcpy(&ctx->tios, &ctx->oldtios, sizeof(struct termios));
	create_locals(&ctx->locals);
	if (ctx->locals == NULL)
		fatal_err(NOMEM, ctx);
	ctx->builtins = getbuiltins();
}
