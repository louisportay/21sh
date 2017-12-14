/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 19:18:10 by lportay           #+#    #+#             */
/*   Updated: 2017/12/14 12:56:11 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Return the flag is 'c' is one
*/

char	ispromptflag(char c)
{
	if (c == 'd' || c == 'H' || c == 'l' || c == 's' || c == 'u' || c == 'w' ||
			c == 'W' || c == '!')
		return (c);
	return (0);
}

/*
** Print the prompt and move the cursor_offset according to the cursor length
*/

static void	print_flag(t_21sh *env, char *s)
{
	env->cursor_offset += ft_strlen(s);
	ft_putstr(s);
}

/*
** Date flag
*/

static void	d_flag(t_21sh *env)
{
	char 		*time_str;
	struct tm	*tm;
	time_t 		t;

	t = time(NULL);
	tm = localtime(&t);
	time_str = asctime(tm);
	time_str[10] = '\0';
	env->cursor_offset += ft_strlen(time_str);//10
	ft_putstr(time_str);
}

/*
** Hostname flag (not truncated)
*/

static void	cap_h_flag(t_21sh *env)
{
	char	hostname[CUSTOM_HOST_NAME_MAX];

	if (gethostname(hostname, CUSTOM_HOST_NAME_MAX) == 0)
		print_flag(env, hostname);
}


/*
** TTY name flag
*/

static void	l_flag(t_21sh *env)
{
	char *s;

	s = NULL;
	if (isatty(STDIN_FILENO) && (s = ttyname(STDIN_FILENO)) && (s = ft_basename(s)))
		print_flag(env, s);
	free(s);
}

/*
** Shell name flag
*/

static void	s_flag(t_21sh *env)
{
	size_t	len;

	len = ft_strlen(SHELLNAME);
	env->cursor_offset += len;
	write(STDOUT_FILENO, SHELLNAME, len);
}

/*
** Username flag
*/

static void	u_flag(t_21sh *env)
{
	struct passwd *pw;

	if ((pw = getpwuid(getuid())))
		print_flag(env, pw->pw_name);
}

/*
** Fullpath Current directory flag
*/

static void	w_flag(t_21sh *env)
{
	char *cwd;
	char *homedir;
	char *tmp;

	homedir = ft_getenv("HOME", env->environ);
	cwd = getcwd(NULL, 0);
	if (cwd && homedir && (tmp = ft_strstr(cwd, homedir)) && tmp == cwd && cwd[ft_strlen(homedir)] == '/')
	{
		env->cursor_offset += ft_strlen(cwd) - ft_strlen(homedir) + 1;
		write(STDOUT_FILENO, "~", 1);
		ft_putstr(cwd + ft_strlen(homedir));
	}
	else if (cwd)
		print_flag(env, cwd);
	free(cwd);
}

/*
** Current directory flag
*/

static void	cap_w_flag(t_21sh *env)
{
	char *cwd;
	char *basename_cwd;

	if ((cwd = getcwd(NULL, 0)) && (basename_cwd = ft_basename(cwd)))
	{
		print_flag(env, basename_cwd);
		free(basename_cwd);
	}
	free(cwd);
}

static void	bang_flag(t_21sh *env)
{
	char *histnum;

	histnum = ft_itoa(env->histindex);
	if (histnum)
		print_flag(env, histnum);
	free(histnum);
}

static void	init_flags(t_prompt_flag *flags)
{
	flags[0] = PROMPT_FLAG(&d_flag, 'd');
	flags[1] = PROMPT_FLAG(&cap_h_flag, 'H');
	flags[2] = PROMPT_FLAG(&l_flag, 'l');
	flags[3] = PROMPT_FLAG(&s_flag, 's');
	flags[4] = PROMPT_FLAG(&u_flag, 'u');
	flags[5] = PROMPT_FLAG(&w_flag, 'w');
	flags[6] = PROMPT_FLAG(&cap_w_flag, 'W');
	flags[7] = PROMPT_FLAG(&bang_flag, '!');
	flags[8] = PROMPT_FLAG(NULL, 0);

}

void	display_prompt(t_21sh *env,	char *prompt_str)
{
	t_prompt_flag	flags[9];
	int				i;
	char			c;

	i = 0;
	init_flags(flags);
	while (*prompt_str)
	{
		if (*prompt_str == '\\' && (c = ispromptflag(*(prompt_str + 1))))
		{
			while (flags[i].flag != c)
				i++;
			flags[i].func(env);
			prompt_str++;
		}
		else
		{
			env->cursor_offset++;
			write(STDOUT_FILENO, prompt_str, 1);
		}
		prompt_str++;
	}
}

void	print_prompt(t_21sh *env)
{
	t_keyval	prompt[5];
	t_hash		*ps;
	int 		i;

	i = 0;
	prompt[0] = KEY_VAL(1, "PS1");
	prompt[1] = KEY_VAL(2, "PS2");
	prompt[2] = KEY_VAL(3, "PS3");
	prompt[3] = KEY_VAL(4, "PS4");
	prompt[4] = KEY_VAL(0, NULL);

	while (prompt[i].key != env->prompt_mode && prompt[i].key)
		i++;
	if (prompt[i].key)
	{
		if ((ps = hashlookup(env->localvar, prompt[i].val)) && ps->data)
			display_prompt(env, (char *)ps->data);
	}
}
