/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initshell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 16:01:14 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/23 14:20:07 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
** returns an array composed of the different paths to look for binary files
*/

char			**getpath(char **environ)
{
	char			**path;
	char			*tpath;

	if ((tpath = ft_astr_getval(environ, "PATH")) == NULL)
		return (NULL);
	if ((path = ft_strsplit(tpath, ':')) == NULL)
		return (NULL);
	if (astr_rmdup(&path) == -1)
	{
		ft_astr_clear(&path);
		return (NULL);
	}
	return (path);
}

/*
** #ifdef __APPLE__
**  ctx->tios.c_cc[VDSUSP] = _POSIX_VDISABLE;
**  ctx->tios.c_cc[VDISCARD] = _POSIX_VDISABLE;
** #endif
*/

static void		init_termios(t_ctx *ctx)
{
	ctx->tios.c_lflag &= ~(ICANON | ECHO);
	ctx->tios.c_cc[VMIN] &= 1;
	ctx->tios.c_cc[VTIME] &= 0;
	ctx->tios.c_cc[VDSUSP] = _POSIX_VDISABLE;
	ctx->tios.c_cc[VDISCARD] = _POSIX_VDISABLE;
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &ctx->tios) == -1)
		ctx->line_edition = 0;
	else
		init_termcaps(ctx);
}

static void		init_line_edition(t_ctx *ctx)
{
	char *tmp;

	if (ctx->istty)
	{
		if (ctx->ret_tcget == -1 || ctx->line_edition == 0
			|| (tmp = getenv("TERM")) == NULL || tgetent(NULL, tmp) == ERR
			|| (ft_strcmp(tmp, "screen") && ft_strcmp(tmp, "xterm")
				&& ft_strcmp(tmp, "xterm-256color") && ft_strcmp(tmp, "linux")))
			ctx->line_edition = 0;
		else
			init_termios(ctx);
	}
	else
		ctx->line_edition = 0;
}

int				init(t_ctx *ctx, char **av, char **environ)
{
	ctx->c_opt = 0;
	init_ctx(ctx, av, environ);
	set_sighandler();
	get_shell_opt(ctx, ctx->av);
	init_line_edition(ctx);
	complete_environ(&ctx->environ);
	ctx->path = getpath(ctx->environ);
	ctx->set |= BRACE_EXPAND;
	init_hist(&ctx->hist, ft_astr_getval(ctx->locals, "HISTFILE"),
												O_CREAT | O_RDWR);
	ctx->pid = getpid();
	return (SUCCESS);
}
