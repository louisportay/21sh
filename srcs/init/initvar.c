/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initvar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 15:55:36 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/31 10:27:47 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			create_locals(char ***locals)
{
	char			hostname[CUSTOM_HOST_NAME_MAX];

	gethostname(hostname, CUSTOM_HOST_NAME_MAX);
	*locals = NULL;
	ft_astr_append(locals, ft_strjoinc(PS1, PS1_VAL, '='));
	ft_astr_append(locals, ft_strjoinc(PS2, PS2_VAL, '='));
	ft_astr_append(locals, ft_strjoinc(PS4, PS4_VAL, '='));
	ft_astr_append(locals, ft_strjoinc("HISTSIZE", HISTSIZE, '='));
	ft_astr_append(locals, ft_strjoinc("HISTFILESIZE", HISTFILESIZE, '='));
	ft_astr_append(locals, ft_strjoinc("HOSTNAME", hostname, '='));
	add_histfile(get_ctxaddr());
	return (SUCCESS);
}

static void	add_home_user_path_var(char ***env)
{
	struct passwd	*pw;

	pw = NULL;
	if ((ft_astr_getkey(*env, "HOME", 4)) == -1)
	{
		pw = getpwuid(getuid());
		ft_astr_append(env, ft_strjoinc("HOME", pw->pw_dir, '='));
	}
	if ((ft_astr_getkey(*env, "USER", 4)) == -1)
	{
		if (!pw)
			pw = getpwuid(getuid());
		ft_astr_append(env, ft_strjoinc("USER", pw->pw_name, '='));
	}
	if ((ft_astr_getkey(*env, "PATH", 4)) == -1)
		ft_astr_append(env, ft_strjoinc("PATH", PATH, '='));
}

/*
** Complete the environ variable with HOME, USER, PATH (if not present)
** and set SHLVL and PWD
*/

void		complete_environ(char ***env)
{
	char			*tmp;
	int				i;

	add_home_user_path_var(env);
	if ((i = ft_astr_getkey(*env, "SHLVL", 5)) == -1)
		ft_astr_append(env, ft_strjoinc("SHLVL", "1", '='));
	else
	{
		tmp = ft_itoa(ft_atoi((*env)[i] + 6) + 1);
		ft_astr_replace(*env, i, ft_strjoinc("SHLVL", tmp, '='));
		free(tmp);
	}
	if ((tmp = getcwd(NULL, 0)) &&
			(i = (ft_astr_getkey(*env, "PWD", 3))) == -1)
	{
		ft_astr_append(env, ft_strjoinc("PWD", tmp, '='));
		free(tmp);
	}
	else if (tmp)
	{
		ft_astr_replace(*env, i, ft_strjoinc("PWD", tmp, '='));
		free(tmp);
	}
}

/*
**	le	->	cursor go one character left
**	nd	->	cursor go one character right
**	im	->	enter insert mode
**	ei	->	exit insert mode
**	dc	->	delete one character
**	cr	->	cursor go to the beginning of the line
**	up	->	cursor go one line up
**	do	->	cursor go one line down
**	cl	->	clear the screen
**	cd	->	clear the line from the cursor until the end of screen
**	sc	->	save cursor position
**	rc	->	restore cursor position
*/

void		init_termcaps(t_ctx *ctx)
{
	ctx->tc.le = tgetstr("le", NULL);
	ctx->tc.nd = tgetstr("nd", NULL);
	ctx->tc.im = tgetstr("im", NULL);
	ctx->tc.ei = tgetstr("ei", NULL);
	ctx->tc.dc = tgetstr("dc", NULL);
	ctx->tc.cr = tgetstr("cr", NULL);
	ctx->tc.up = tgetstr("up", NULL);
	ctx->tc.dow = tgetstr("do", NULL);
	ctx->tc.cl = tgetstr("cl", NULL);
	ctx->tc.cd = tgetstr("cd", NULL);
	ctx->tc.sc = tgetstr("sc", NULL);
	ctx->tc.rc = tgetstr("rc", NULL);
	if (!ctx->tc.le || !ctx->tc.nd || !ctx->tc.im || !ctx->tc.ei
		|| !ctx->tc.dc || !ctx->tc.cr || !ctx->tc.up || !ctx->tc.dow
		|| !ctx->tc.cl || !ctx->tc.cd)
	{
		ctx->line_edition = false;
		ctx->history = false;
	}
}

/*
** Finish History + exit built-ins
*/

t_hdict		*getbuiltins(void)
{
	t_hdict		*dict;

	dict = hash_create(HASH_SIZE, HASH_PRIME);
	hash_add(dict, "exit", &ft_exit);
	hash_add(dict, "history", &ft_history);
	hash_add(dict, "cd", &ft_cd);
	hash_add(dict, "echo", &ft_echo);
	hash_add(dict, "printenv", &ft_printenv);
	hash_add(dict, "hash", &ft_hash);
	hash_add(dict, "set", &ft_set);
	hash_add(dict, "setenv", &ft_setenv);
	hash_add(dict, "export", &ft_export);
	hash_add(dict, "unsetenv", &ft_unsetenv);
	hash_add(dict, "unset", &ft_unset);
	return (dict);
}
