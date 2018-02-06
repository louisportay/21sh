/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 19:23:05 by lportay           #+#    #+#             */
/*   Updated: 2018/02/06 18:10:06 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int	init_local(t_21sh *env)
{
	char	hostname[CUSTOM_HOST_NAME_MAX];
	t_kvp 	local[7];

	gethostname(hostname, CUSTOM_HOST_NAME_MAX);
	local[0] = KVP(PS1, PS1_VAL);
	local[1] = KVP(PS2, PS2_VAL);
	local[2] = KVP(PS4, PS4_VAL);
	local[3] = KVP("HISTSIZE", HISTSIZE);
	local[4] = KVP("HISTFILESIZE", HISTFILESIZE);
	local[5] = KVP("HOSTNAME", hostname);
	local[6] = KVP(NULL, NULL);

	if (!(env->local = copy_stack_kvp(local, 6)))
		return (NOMEM);
	set_kvp(ft_strdup("HISTFILE"), get_histfile(env), &env->local);
	return (SUCCESS);
}

static int	init_env_var(t_kvp *env_var, char *exec_file, t_21sh *env)
{
	char *tmp;
	char *path;

	if ((tmp = getcwd(NULL, 0)) == NULL)
		return (NODIR);
	env_var[0] = KVP(ft_strdup("PWD"), tmp);

	if (*exec_file == '/')
		tmp = ft_strdup(exec_file);
	else if (*exec_file == '.')
		tmp = ft_strexpand(exec_file, '.', tmp);
	else if ((path = get_kvp("PATH", env->environ)))
		tmp = getpath(path, exec_file);
	else
		tmp = NULL;
	env_var[1] = KVP(ft_strdup("SHELL"), tmp);

	if ((tmp = get_kvp("SHLVL", env->environ)))
		tmp = ft_itoa(ft_atoi(tmp) + 1);
	else
		tmp = ft_strdup("1");
	env_var[2] = KVP(ft_strdup("SHLVL"), tmp);

	env_var[3] = KVP(NULL, NULL);
	return (SUCCESS);
}

static void	complete_existing_environ(t_kvp **environ)
{
	struct passwd *pw;

	pw = NULL;
	if (!(get_kvp("HOME", *environ)))
	{
		pw = getpwuid(getuid());
		set_kvp(ft_strdup("HOME"), ft_strdup(pw->pw_dir), environ);
	}
	if (!(get_kvp("USER", *environ)))
	{
		if (!pw)
			pw = getpwuid(getuid());
		set_kvp(ft_strdup("USER"), ft_strdup(pw->pw_name), environ);
	}
	if (!(get_kvp("PATH", *environ)))
		set_kvp(ft_strdup("PATH"), ft_strdup(PATH), environ);
}

static int	init_environ(t_21sh *env, char **av, char **environ)
{
	t_kvp 	var[4];
	int		i;

	env->environ = copy_kvp_env(environ);
	if (init_env_var(var, *av, env) != SUCCESS)
		return (NODIR);
	i = 0;
	while (var[i].val != NULL)
	{
		if (set_kvp(var[i].key, var[i].val, &env->environ) == -1)
			return (NOMEM);
		i++;
	}
	complete_existing_environ(&env->environ);
	return (SUCCESS);
}

void init_termcaps(t_21sh *env)
{
		env->tc.le = tgetstr("le", NULL);//		cursor go one character left
		env->tc.nd = tgetstr("nd", NULL);//		cursor go one character right
		env->tc.im = tgetstr("im", NULL);//		enter insert mode
		env->tc.ei = tgetstr("ei", NULL);//		exit insert mode
		env->tc.dc = tgetstr("dc", NULL);//		delete one character
		env->tc.cr = tgetstr("cr", NULL);//		cursor go to the beginning of the line
		env->tc.up = tgetstr("up", NULL);//		cursor go one line up
		env->tc.dow = tgetstr("do", NULL);//		cursor go one line down
		env->tc.cl = tgetstr("cl", NULL);//		clear the screen
		env->tc.cd = tgetstr("cd", NULL);//		clear the line from the cursor until the end of screen
		env->tc.sc = tgetstr("sc", NULL);//		save cursor position
		env->tc.rc = tgetstr("rc", NULL);//		restore cursor position
		if (!env->tc.le || !env->tc.nd || !env->tc.im || !env->tc.ei || !env->tc.dc || !env->tc.cr || !env->tc.up || !env->tc.dow || !env->tc.cl || !env->tc.cd)
			env->line_edition = false;
}

static void	init_termios(t_21sh *env)
{
		env->tios.c_lflag &= ~(ICANON | ECHO);
		env->tios.c_cc[VMIN] &= 1;
		env->tios.c_cc[VTIME] &= 0;
		env->tios.c_cc[VDSUSP] = _POSIX_VDISABLE;
		env->tios.c_cc[VDISCARD] = _POSIX_VDISABLE;

		if (tcsetattr(STDIN_FILENO, TCSADRAIN, &env->tios) == -1)
			env->line_edition = false;
		else
			init_termcaps(env);
}

//mettre les variables dans l'ordre dans lequel elles ont ete declarees (les declarer dans un ordre logique)

static void	init_env_values(t_21sh *env)
{
	env->cur_line = NULL;
	env->heredoc_eof = NULL;

	env->line.line = NULL;
	env->line.lastline = NULL;
	env->line.yank = NULL;
	env->line.linestate = NULL;

	env->hist.file = 0;
	env->hist.list = NULL;
	env->hist.index = 1;

	env->toklist = NULL;

	env->history = true;
	env->line_edition = true;
	env->emacs_mode = true;
	env->istty = isatty(STDIN_FILENO);

}

t_21sh *get_envaddr(t_21sh *envaddr)
{
	static t_21sh *env = NULL;

	if (envaddr)
		env = envaddr;
	return (env);
}

//on garde la comparaison avec xterm-256color ?

static int	init(t_21sh *env, char **av, char **environ)
{
	char	*tmp;
	int		ret;

	get_envaddr(env);
	init_env_values(env);
	if (tcgetattr(STDIN_FILENO, &env->oldtios) == -1 || tcgetattr(STDIN_FILENO,
&env->tios) == -1 || !(env->istty) || (tmp = getenv("TERM")) == NULL ||
ft_strcmp(tmp, "xterm-256color") ||tgetent(NULL, tmp) == ERR)
		env->line_edition = false;
	else
		init_termios(env);
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &env->ws) == -1)
		env->line_edition = false;
	if (wrap_signal() == FAILSETSIGHDLR)
		return (FAILSETSIGHDLR);
	if ((ret = init_environ(env, av, environ)) != SUCCESS)
		return (ret);
	if ((ret = init_local(env)) != SUCCESS)
		return (ret);
	if (env->history)
		init_hist(env);
	return (SUCCESS);
}

void	vingtetunsh(char **av, char  **environ)
{
	t_21sh	env;
	char	ret;

	if ((ret = init(&env, av, environ)) != SUCCESS)
		fatal_err(ret, &env);

	while (1)//
	{
		wrap_lineread(&env, &env.line, PS1);

		if (env.line.split_line)
			env.toklist = tokenizer(env.line.split_line);

		delete_toklist(&env.toklist);

		if (env.line.line_saved == false)
			ft_dlstdel(&env.line.split_line, &delvoid);
		else//
			ft_dlstremove(&env.line.final_newline, &delvoid);
	}
	wrap_exit(EXIT_SUCCESS, &env);
}
