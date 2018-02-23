/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 16:01:14 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/23 10:28:31 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

//mettre les variables dans l'ordre dans lequel elles ont ete declarees (les declarer dans un ordre logique)
//editer les options en fonction de *av donnés

static void			init_ctx(t_ctx *ctx, char **av, char **environ)
{
	ctx->av = av;
	ctx->cur_line = NULL;
	ctx->heredoc_eof = NULL;
	ctx->line.line = NULL;
	ctx->line.yank = NULL;
	ctx->line.lastline = NULL;
	ctx->line.linestate = NULL;
	ctx->hist.file = 0;
	ctx->hist.list = NULL;
	ctx->hist.index = 1;
	ctx->toklist = NULL;//
	ctx->emacs_mode = 1;
	ctx->line_edition = 1;
	ctx->config_file = 1;
	ctx->history = 1;
	ctx->job_control = 1;
	ctx->istty = isatty(STDIN_FILENO);
	ctx->fd = ctx->istty ? STDIN_FILENO : -1;
	ctx->path = getpath(environ);
	ctx->environ = ft_astr_dup(environ);
	ctx->hash = hash_create(HASH_SIZE, HASH_PRIME);
}

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
}

static void			init_termios(t_ctx *ctx)
{
	ft_memcpy(&ctx->tios, &ctx->oldtios, sizeof(struct termios));
	ctx->tios.c_lflag &= ~(ICANON | ECHO);
	ctx->tios.c_cc[VMIN] &= 1;
	ctx->tios.c_cc[VTIME] &= 0;
#ifdef __APPLE__
	ctx->tios.c_cc[VDSUSP] = _POSIX_VDISABLE;
	ctx->tios.c_cc[VDISCARD] = _POSIX_VDISABLE;
#endif
	ctx->tios.c_cc[VINTR] = _POSIX_VDISABLE;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ctx->ws) == -1)
		ctx->line_edition = false;
	else if (tcsetattr(STDIN_FILENO, TCSADRAIN, &ctx->tios) == -1)
		ctx->line_edition = false;
	else
		init_termcaps(ctx);
}

//on garde la comparaison avec xterm-256color ?

static int	init_terminal(t_ctx *ctx)
{
	char *tmp;

	if (ctx->istty)
	{
		init_job_control(ctx);
		if (tcgetattr(ctx->fd, &ctx->oldtios) == -1 || ctx->line_edition == 0 || (tmp = getenv("TERM")) == NULL
				|| tgetent(NULL, tmp) == ERR)/*ft_strcmp(tmp, "xterm-256color") ||*/
		{
			ft_memcpy(&ctx->tios, &ctx->oldtios, sizeof(struct termios));
			ctx->line_edition = false;
			ctx->history = false;
			return (-1);
		}
		init_termios(ctx);
	}
	else
	{
		ctx->line_edition = false;
		ctx->history = false;
	//	ctx->job_control = false;
	}
	return (0);
}

int	init(t_ctx *ctx, char **av, char **environ)
{
	char	*tmp;

	get_ctxaddr(ctx);
	init_ctx(ctx, av, environ);
	getopt_21sh(ctx, ctx->av);
	init_terminal(ctx);
	if (set_sighandler() == FAILSETSIGHDLR)
		return (FAILSETSIGHDLR);

	create_locals(&ctx->locals);
	complete_environ(&ctx->environ);

	ft_astr_append(&ctx->locals, ft_strjoinc("HISTFILE", tmp = get_histfile(ctx), '='));
	free(tmp);
	ctx->builtins = getbuiltins();
	if (ctx->history)
		init_hist(ctx);
	return (SUCCESS);
}
