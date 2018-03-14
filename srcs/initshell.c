/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 16:01:14 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/14 12:22:00 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void			init_job_control(t_ctx *ctx)
{
	while (tcgetpgrp(ctx->fd) != (ctx->pid = getpgrp()))
		kill(-ctx->pgid, SIGTTIN);
	ctx->pgid = getpid();
	if (setpgid(ctx->pgid, ctx->pgid) < 0)
	{
		ctx->job_control = 0;
		perror("setpgid");
	}
	if (tcsetpgrp(ctx->fd, ctx->pgid) != 0)
		dprintf(STDERR_FILENO, "init job ctrl tcsetgrp error\n");
	ctx->bg_cnt = DFL_BGCNT;
	ctx->bg_jobs = (t_job **)ft_pmemalloc(sizeof(t_job *) * DFL_BGCNT,
											&on_emem, NOMEM);
}

//mettre les variables dans l'ordre dans lequel elles ont ete declarees (les declarer dans un ordre logique)

static void			init_ctx(t_ctx *ctx, char **av, char **environ)
{
	ctx->av = av;
	ctx->cur_line = NULL;
	ctx->line.line = NULL;
	ctx->line.yank = NULL;
	ctx->line.lastline = NULL;
	ctx->line.linestate = NULL;
	ctx->line.heredoc = 0;

	ctx->hist.list = NULL;
	ctx->hist.index = 1;

	ctx->emacs_mode = 1;
	ctx->line_edition = 1;
	ctx->config_file = 1;
	ctx->history = 1;
	ctx->job_control = 1;

	ctx->fd = STDIN_FILENO;
	ctx->tty = open("/dev/tty", O_RDWR);
	ctx->istty = isatty(STDIN_FILENO);
	if (ioctl(ctx->fd, TIOCGWINSZ, &ctx->ws) == -1)
		ctx->line_edition = false;

	ctx->path = getpath(environ);
	ctx->environ = ft_astr_dup(environ);
	ctx->hash = hash_create(HASH_SIZE, HASH_PRIME);

	ctx->ret_tcget = tcgetattr(ctx->fd, &ctx->oldtios);
	ft_memcpy(&ctx->tios, &ctx->oldtios, sizeof(struct termios));
	create_locals(&ctx->locals);
	ctx->builtins = getbuiltins();
	if (ctx->istty)
		init_job_control(ctx);
}

static void			init_termios(t_ctx *ctx)
{
	ctx->tios.c_lflag &= ~(ICANON | ECHO);
	ctx->tios.c_cc[VMIN] &= 1;
	ctx->tios.c_cc[VTIME] &= 0;
#ifdef __APPLE__
	ctx->tios.c_cc[VDSUSP] = _POSIX_VDISABLE;
	ctx->tios.c_cc[VDISCARD] = _POSIX_VDISABLE;
#endif
	ctx->tios.c_cc[VINTR] = _POSIX_VDISABLE;
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &ctx->tios) == -1)
		ctx->line_edition = false;
	else
		init_termcaps(ctx);
}

//on garde la comparaison avec xterm-256color ?

static void	init_line_edition(t_ctx *ctx)
{
	char *tmp;

	if (ctx->istty)
	{
		if (ctx->ret_tcget == -1 || ctx->line_edition == 0 || (tmp = getenv("TERM")) == NULL
				|| tgetent(NULL, tmp) == ERR)/*ft_strcmp(tmp, "xterm-256color") ||*/
			ctx->line_edition = false;
		else
			init_termios(ctx);
	}
	else
		ctx->line_edition = false;
}

int	init(t_ctx *ctx, char **av, char **environ)
{
	init_ctx(ctx, av, environ);
	set_sighandler();
	get_shell_opt(ctx, ctx->av);
	init_line_edition(ctx);
	complete_environ(&ctx->environ);
	init_hist(&ctx->hist);
	return (SUCCESS);
}
