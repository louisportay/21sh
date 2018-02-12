/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initvar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 15:55:36 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/12 16:28:53 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int					create_locals(char ***locals)
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
	return (SUCCESS);
}

/*
** Complete the environ variable with HOME, USER, PATH (if not present)
** and set SHLVL and PWD
*/

void				complete_environ(char ***environ)
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

void				init_termcaps(t_ctx *ctx)
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
		ctx->line_edition = false;
}

t_hash_dict			*getbuiltins(void)
{
	t_hash_dict		*dict;

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
