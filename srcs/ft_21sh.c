/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 19:23:05 by lportay           #+#    #+#             */
/*   Updated: 2018/02/11 20:04:19 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	create_locals(char ***locals)
{
	char	hostname[CUSTOM_HOST_NAME_MAX];

	gethostname(hostname, CUSTOM_HOST_NAME_MAX);
	*locals = NULL;

	ft_astr_append(locals, ft_strjoinc(PS1, PS1_VAL, '='));
	ft_astr_append(locals, ft_strjoinc(PS2, PS2_VAL, '='));
	ft_astr_append(locals, ft_strjoinc(PS4, PS4_VAL, '='));
	ft_astr_append(locals, ft_strjoinc("HISTSIZE", HISTSIZE, '='));
	ft_astr_append(locals, ft_strjoinc("HISTFILESIZE", HISTFILESIZE, '='));
	ft_astr_append(locals, ft_strjoinc("HOSTNAME", hostname, '='));

	return (SUCCESS);
}

//SHELL var

//	if (*exec_file == '/')
//		tmp = ft_strdup(exec_file);
//	else if (*exec_file == '.')
//		tmp = ft_strexpand(exec_file, '.', tmp);
//	else if ((path = get_kvp("PATH", ctx->environ)))
//		tmp = getpath(path, exec_file);
//	else
//		tmp = NULL;

/*
** Complete the environ variable with HOME, USER, PATH (if not present)
** and set SHLVL and PWD
*/

static void	complete_environ(char ***environ)
{
	struct passwd	*pw;
	char			*tmp;

	pw = NULL;
	if ((ft_astr_getkey(*environ, "HOME", 4)) == -1)
	{
		pw = getpwuid(getuid());
		ft_astr_append(environ, ft_strjoinc("HOME", pw->pw_dir, '='));
	}
	if ((ft_astr_getkey(*environ, "USER", 4)) == -1)
	{
		if (!pw)
			pw = getpwuid(getuid());
		ft_astr_append(environ, ft_strjoinc("USER", pw->pw_name, '='));
	}
	if ((ft_astr_getkey(*environ, "PATH", 4)) == -1)
		ft_astr_append(environ, ft_strjoinc("PATH", PATH, '='));

	if (!(tmp = ft_astr_getval(*environ, "SHLVL")))
		ft_astr_append(environ, ft_strjoinc("SHLVL", "1", '='));
	else
	{
		tmp = ft_itoa(ft_atoi(tmp) + 1);
		ft_astr_append(environ, ft_strjoinc("SHLVL", tmp, '='));
		free(tmp);
	}
	if ((tmp = getcwd(NULL, 0)))
	{
		ft_astr_append(environ, ft_strjoinc("PWD", tmp, '='));
		free(tmp);
	}
}

/*
** returns an array composed of the different paths to look for binary files
*/

char	**getpath(char **environ)
{
	char	**path;
	int		i;

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














void init_termcaps(t_ctx *ctx)
{
		ctx->tc.le = tgetstr("le", NULL);//		cursor go one character left
		ctx->tc.nd = tgetstr("nd", NULL);//		cursor go one character right
		ctx->tc.im = tgetstr("im", NULL);//		enter insert mode
		ctx->tc.ei = tgetstr("ei", NULL);//		exit insert mode
		ctx->tc.dc = tgetstr("dc", NULL);//		delete one character
		ctx->tc.cr = tgetstr("cr", NULL);//		cursor go to the beginning of the line
		ctx->tc.up = tgetstr("up", NULL);//		cursor go one line up
		ctx->tc.dow = tgetstr("do", NULL);//		cursor go one line down
		ctx->tc.cl = tgetstr("cl", NULL);//		clear the screen
		ctx->tc.cd = tgetstr("cd", NULL);//		clear the line from the cursor until the end of screen
		ctx->tc.sc = tgetstr("sc", NULL);//		save cursor position
		ctx->tc.rc = tgetstr("rc", NULL);//		restore cursor position
		if (!ctx->tc.le || !ctx->tc.nd || !ctx->tc.im || !ctx->tc.ei ||
		!ctx->tc.dc || !ctx->tc.cr || !ctx->tc.up || !ctx->tc.dow ||
		!ctx->tc.cl || !ctx->tc.cd)
			ctx->line_edition = false;
}

static void	init_termios(t_ctx *ctx)
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

//mettre les variables dans l'ordre dans lequel elles ont ete declarees (les declarer dans un ordre logique)

static void	init_ctx(t_ctx *ctx, char **av, char **environ)
{
	(void)av;//
	ctx->cur_line = NULL;
	ctx->heredoc_eof = NULL;

	ctx->line.line = NULL;
	ctx->line.lastline = NULL;
	ctx->line.yank = NULL;
	ctx->line.linestate = NULL;
	ctx->hist.file = 0;
	ctx->hist.list = NULL;
	ctx->hist.index = 1;

	ctx->toklist = NULL;//

	//editer les options en fonction de *av
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

t_ctx *get_ctxaddr(t_ctx *ctxaddr)
{
	static t_ctx *ctx = NULL;

	if (ctxaddr)
		ctx = ctxaddr;
	return (ctx);
}

void	init_job_control(t_ctx *ctx)
{
	while (tcgetpgrp (ctx->fd) != (ctx->pid = getpgrp ()))
		kill (- ctx->pgid, SIGTTIN);
	ctx->pgid = getpid ();
	if (setpgid (ctx->pgid, ctx->pgid) < 0)
		ctx->job_control = 0;
	tcsetpgrp (ctx->fd, ctx->pgid);
}

t_hash_dict *getbuiltins(void)
{
	t_hash_dict *dict;

	dict = ft_hashset_create(HASH_SIZE, HASH_PRIME); 
//	ft_hashset_add(dict, "bang", &);
//	ft_hashset_add(dict, "cd", &);
//	ft_hashset_add(dict, "echo", &);
//	ft_hashset_add(dict, "env", &);
//	ft_hashset_add(dict, "hash", &);
//	ft_hashset_add(dict, "history", &);
//	ft_hashset_add(dict, "export", &);
//	ft_hashset_add(dict, "set", &);
//	ft_hashset_add(dict, "setenv", &);
//	ft_hashset_add(dict, "unsetenv", &);
//	ft_hashset_add(dict, "shopt", &);// on le garde ?
	return (dict);
}

//on garde la comparaison avec xterm-256color ?

static int	init(t_ctx *ctx, char **av, char **environ)
{
	char	*tmp;
	int		ret;

	get_ctxaddr(ctx);

	init_ctx(ctx, av, environ);
	complete_environ(&ctx->environ);
	if (ctx->istty)
		init_job_control(ctx);

	ret = tcgetattr(ctx->fd, &ctx->oldtios);
	ft_memcpy(&ctx->tios, &ctx->oldtios, sizeof(struct termios));

	if (ret == -1 || !(ctx->istty) || (tmp = getenv("TERM")) == NULL ||/*ft_strcmp(tmp, "xterm-256color") ||*/
			tgetent(NULL, tmp) == ERR)
		ctx->line_edition = false;
	else
		init_termios(ctx);

	if (set_sighandler() == FAILSETSIGHDLR)
		return (FAILSETSIGHDLR);


	create_locals(&ctx->locals);
	ft_astr_append(&ctx->locals, ft_strjoinc("HISTFILE", tmp = get_histfile(ctx), '='));
	if (ft_strlen(tmp))
		free(tmp);
//	ctx->builtins = getbuiltins();
	init_hist(ctx);
	return (SUCCESS);
}

void	vingtetunsh(char **av, char  **environ)
{
	t_ctx	ctx;
	char	ret;
	t_ptok *extree;

	if ((ret = init(&ctx, av, environ)) != SUCCESS)
		fatal_err(ret, &ctx);

	while (1)//
	{
		wrap_lineread(&ctx, &ctx.line, PS1);

		if (ctx.line.split_line)
			ctx.toklist = tokenizer(ctx.line.split_line);
		if (ctx.toklist != NULL)
			extree = parse(ctx.toklist);
		ptok_print(extree);

		delete_toklist(&ctx.toklist);
		if (ctx.line.line_saved == false)
			ft_dlstdel(&ctx.line.split_line, &delvoid);
		else//
			ft_dlstremove(&ctx.line.final_newline, &delvoid);
	}
	wrap_exit(EXIT_SUCCESS, &ctx);
}
