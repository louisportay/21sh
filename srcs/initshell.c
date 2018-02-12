/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 16:01:14 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/12 16:21:30 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** returns an array composed of the different paths to look for binary files
*/

static char			**getpath(char **environ)
{
	char			**path;
	int				i;

	if ((i = ft_astr_getkey(environ, "PATH", 4)) == -1)
		return (NULL);
	if (!(path = ft_strsplit(environ[i], ':')))
		return (NULL);
	if (astr_rmdup(&path) == -1)
	{
		ft_astr_clear(&path);
		return (NULL);
	}
	return (path);
}

//mettre les variables dans l'ordre dans lequel elles ont ete declarees (les declarer dans un ordre logique)

static void			init_ctx(t_ctx *ctx, char **av, char **environ)
{
	(void)av;//
	ctx->cur_line = NULL;
	ctx->heredoc_eof = NULL;
	ctx->line.line = NULL;
	ctx->line.lastline = NULL;
	ctx->line.linestate = NULL;
	ctx->hist.file = 0;
	ctx->hist.list = NULL;
	ctx->hist.index = 1;
	ctx->toklist = NULL;//
	ctx->emacs_mode = 1;
	ctx->line_edition = 1;
	ctx->history = 1;
	ctx->job_control = 1;
	ctx->fd = STDIN_FILENO;
	ctx->istty = isatty(ctx->fd);
	ctx->path = getpath(environ);
	ctx->environ = ft_astr_dup(environ);
	ctx->hash = ft_hashset_create(HASH_SIZE, HASH_PRIME);
}

static void			init_job_control(t_ctx *ctx)
{
	while (tcgetpgrp(ctx->fd) != (ctx->pid = getpgrp()))
		kill(-ctx->pgid, SIGTTIN);
	ctx->pgid = getpid();
	if (setpgid(ctx->pgid, ctx->pgid) < 0)
		ctx->job_control = 0;
	tcsetpgrp(ctx->fd, ctx->pgid);
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
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ctx->ws) == -1)
		ctx->line_edition = false;
	else if (tcsetattr(STDIN_FILENO, TCSADRAIN, &ctx->tios) == -1)
		ctx->line_edition = false;
	else
		init_termcaps(ctx);
}

int					init(t_ctx *ctx, char **av, char **environ)
{
	char			*tmp;
	int				ret;

	get_ctxaddr(ctx);
	init_ctx(ctx, av, environ);
	complete_environ(&ctx->environ);
	if (ctx->istty)
		init_job_control(ctx);
	ret = tcgetattr(ctx->fd, &ctx->oldtios);
	ft_memcpy(&ctx->tios, &ctx->oldtios, sizeof(struct termios));
	if (ret == -1 || !(ctx->istty) || (tmp = getenv("TERM")) == NULL
//		|| ft_strcmp(tmp, "xterm-256color") || if only xterm-256color
		|| tgetent(NULL, tmp) == ERR)
		ctx->line_edition = false;
	else
		init_termios(ctx);
	if (set_sighandler() == FAILSETSIGHDLR)
		return (FAILSETSIGHDLR);
	create_locals(&ctx->locals);
	ft_astr_append(&ctx->locals,
					ft_strjoinc("HISTFILE", tmp = get_histfile(ctx), '='));
	if (ft_strlen(tmp))
		free(tmp);
//	ctx->builtins = getbuiltins();
	init_hist(ctx);
	return (SUCCESS);
}
