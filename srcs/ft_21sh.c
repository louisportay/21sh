/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_21sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 19:23:05 by lportay           #+#    #+#             */
/*   Updated: 2018/01/02 10:43:50 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Insert safely one entry in the local variables table
*/

int			fill_localtable(t_hash **localvar, char *key, char *value)
{
	t_hash	*tmp;

	if (!(tmp = hashcreate(key, value, ft_strlen(value) + 1)))
		return (NOMEM);
	hashinsert(localvar, tmp, 0, &ft_memdel);
	return (SUCCESS);
}

/*
** Will init few local variables each time called,
** Also erase everything present in the table
** Can be used to reset all the local variables
*/

static int	init_local(t_21sh *env)
{
	char	hostname[CUSTOM_HOST_NAME_MAX];
	t_var 	locals[7];
	int		i;

	i = 0;
	hashclear(env->localvar, &ft_memdel);
	gethostname(hostname, CUSTOM_HOST_NAME_MAX);
	locals[0] = VAR("PS1", PS1_VAL);
	locals[1] = VAR("PS2", PS2_VAL);
	locals[2] = VAR("PS4", PS4_VAL);
	locals[3] = VAR("HISTSIZE", HISTSIZE);
	locals[4] = VAR("HISTFILESIZE", HISTFILESIZE);
	locals[5] = VAR("HOSTNAME", hostname);
	locals[6] = VAR(NULL, NULL);
	while (locals[i].key)
		if (fill_localtable(env->localvar, locals[i].key, locals[i].val) == NOMEM)
				return (NOMEM);
		else
			i++;
	if (get_histfile(env) == NOMEM)
		return (NOMEM);
	return (SUCCESS);
}

static int	init_env_var(t_var *env_var, char *exec_file, t_21sh *env)
{
	char *tmp;
	char *path;

	env_var[3] = VAR(NULL, NULL);
	if ((tmp = getcwd(NULL, 0)) == NULL)
		return (NODIR);
	env_var[0] = VAR("PWD", tmp);
	if (*exec_file == '/')
		tmp = ft_strdup(exec_file);
	else if (*exec_file == '.')
		tmp = ft_strexpand(exec_file, '.', tmp);
	else if ((path = ft_getenv("PATH", env->environ)))
		tmp = getpath(path, exec_file);
	else
		tmp = NULL;
	env_var[1] = VAR("SHELL", tmp);
	if ((tmp = ft_getenv("SHLVL", env->environ)))
		tmp = ft_itoa(ft_atoi(tmp) + 1);
	else
		tmp = ft_strdup("1");
	env_var[2] = VAR("SHLVL", tmp);
	return (SUCCESS);
}

// garder le PATH ?

static void	complete_existing_environ(t_21sh *env)
{
	struct passwd *pw;

	pw = NULL;
	if (!(ft_getenv("HOME", env->environ)))
	{
		pw = getpwuid(getuid());
		ft_setenv("HOME", pw->pw_dir, 1, &env->environ);
	}
	if (!(ft_getenv("USER", env->environ)))
	{
		if (!pw)
			pw = getpwuid(getuid());
		ft_setenv("USER", pw->pw_name, 1, &env->environ);
	}
	if (!(ft_getenv("PATH", env->environ)))
		ft_setenv("PATH", "/usr/local/bin/:/usr/bin:/bin", 1, &env->environ);
}

static int	init_environ(char **av, t_21sh *env)
{
	t_var 	var[4];
	int		i;

	if ((i = init_env_var(var, *av, env)) != SUCCESS)
		return (NODIR);
	i = 0;
	while (var[i].key != NULL)
	{
		if (ft_setenv(var[i].key, var[i].val, 1, &env->environ) == -1)
		{
			while (var[i].key)
				free(var[i++].val);
			return (NOMEM);
		}
		free(var[i].val);
		i++;
	}
	complete_existing_environ(env);
	return (SUCCESS);
}

static void	init_termios(t_21sh *env)
{
		env->tios.c_lflag &= ~(ICANON | ECHO);
		env->tios.c_cc[VMIN] &= 1;
		env->tios.c_cc[VTIME] &= 0;
		env->tc.le = tgetstr("le", NULL);//		cursor go one character left
		env->tc.nd = tgetstr("nd", NULL);//		cursor go one character right
		env->tc.im = tgetstr("im", NULL);//		enter insert mode
		env->tc.ei = tgetstr("ei", NULL);//		exit insert mode
		env->tc.dc = tgetstr("dc", NULL);//		delete one character
		env->tc.cr = tgetstr("cr", NULL);//		cursor go to the beginning of the line
		env->tc.up = tgetstr("up", NULL);//		cursor go one line up
		env->tc.dow = tgetstr("do", NULL);//	cursor go one line down
		env->tc.cl = tgetstr("cl", NULL);//		clear the screen
		env->tc.cd = tgetstr("cd", NULL);//		clear the line from the cursor until the end of screen
		env->tc.sc = tgetstr("sc", NULL);//		save cursor position
		env->tc.rc = tgetstr("rc", NULL);//		restore cursor position

		if (tcsetattr(STDIN_FILENO, TCSADRAIN, &env->tios) == -1 || !env->tc.le || !env->tc.nd || !env->tc.im || !env->tc.ei || !env->tc.dc || !env->tc.cr || !env->tc.up || !env->tc.dow || !env->tc.cl || !env->tc.cd)
			env->line_edition = false;	
}

//mettre les variables dans l'ordre dans lequel elles ont ete declarees

static void	init_values(t_21sh *env)
{
	env->environ = NULL;
	hashinit(env->localvar);

	env->line = NULL;
	env->lastline = NULL;
	env->yank = NULL;
	env->linestate = NULL;

//	env->toklist = NULL;//

	env->history = true;
	env->line_edition = true;

	env->histfile = 0;
	env->histlist = NULL;
	env->histindex = 1;

	env->emacs_mode = true;
}

static int	init(t_21sh *env, char **av, char **environ)
{
	char	*tmp;
	int		ret;

	init_values(env);
	if (tcgetattr(STDIN_FILENO, &env->oldtios) == -1 || tcgetattr(STDIN_FILENO, &env->tios) == -1 || !isatty(STDIN_FILENO) ||
		(tmp = getenv("TERM")) == NULL || tgetent(NULL, tmp) == ERR)
		env->line_edition = false;
	else
		init_termios(env);
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &env->ws) == -1)
		env->line_edition = false;
	if (wrap_signal() == FAILSETSIGHDLR)
		return (FAILSETSIGHDLR);
	if (!(env->environ = ft_copyenv(environ)))
		return (NOENVIRON);
	if ((ret = init_environ(av, env)) != SUCCESS)
		return (ret);
	if ((ret = init_local(env)) != SUCCESS)
		return (ret);
	if (env->history)
		init_hist(env);
	sig_switch(0, env);
	return (SUCCESS);
}

void	vingtetunsh(char **av, char  **environ)
{
	t_21sh	env;
	char	ret;

	if ((ret = init(&env, av, environ)) != SUCCESS)
		fatal_err(ret, &env);

	if (env.line_edition == true)
		while (1)//
		{
			wrap_lineread(&env);
			env.toklist = tokenizer(env.split_line);

			delete_toklist(&env.toklist);
			if (env.line_saved == false)
				ft_dlstdel(&env.split_line, &delvoid);
			else//
				ft_dlstremove(&env.final_newline, &delvoid);
		}
//	else
//		while (1)
//			getrawline(&env);
	wrap_exit(EXIT_SUCCESS, &env);
}
