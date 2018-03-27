/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ctx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 19:37:06 by lportay           #+#    #+#             */
/*   Updated: 2018/03/26 18:34:22 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	init_job_control(t_ctx *ctx)
{
	while (tcgetpgrp(ctx->fd) != (ctx->pid = getpgrp()))
		kill(-ctx->pgid, SIGTTIN);
	ctx->pgid = getpid();
	if (setpgid(ctx->pgid, ctx->pgid) < 0)
		ctx->job_control = 0;
	if (tcsetpgrp(ctx->fd, ctx->pgid) != 0)
		ft_dprintf(STDERR_FILENO, "init job ctrl tcsetgrp error\n");
	ctx->bg_cnt = DFL_BGCNT;
	ctx->bg_jobs = (t_job **)ft_pmemalloc(sizeof(t_job *) * DFL_BGCNT,
											&on_emem, NOMEM);
}

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
	ctx->fd = STDIN_FILENO;
	ctx->tty = open("/dev/tty", O_RDWR);
	ctx->istty = isatty(STDIN_FILENO);
	if (!ctx->istty || ioctl(ctx->fd, TIOCGWINSZ, &ctx->ws) == -1)
		ctx->line_edition = 0;
	ctx->environ = ft_astr_dup(environ);
	ctx->hash = hash_create(HASH_SIZE, HASH_PRIME);
	ctx->ret_tcget = tcgetattr(ctx->fd, &ctx->oldtios);
	ft_memcpy(&ctx->tios, &ctx->oldtios, sizeof(struct termios));
	create_locals(&ctx->locals);
	ctx->builtins = getbuiltins();
	if (ctx->istty)
		init_job_control(ctx);
}
