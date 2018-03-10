/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 19:18:10 by lportay           #+#    #+#             */
/*   Updated: 2018/03/10 20:51:01 by lportay          ###   ########.fr       */
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

static void	print_flag(t_ctx *ctx, char *s)
{
	ctx->cur_line->cursor_offset += ft_strlen(s);
	ft_putstr(s);
}

/*
** Date flag
*/

static void	d_flag(t_ctx *ctx)
{
	char 		*time_str;
	struct tm	*tm;
	time_t 		t;

	t = time(NULL);
	tm = localtime(&t);
	time_str = asctime(tm);
	time_str[10] = '\0';
	ctx->cur_line->cursor_offset += ft_strlen(time_str);//10
	ft_putstr(time_str);
}

/*
** Hostname flag (not truncated)
*/

static void	cap_h_flag(t_ctx *ctx)
{
	char	hostname[CUSTOM_HOST_NAME_MAX];

	if (gethostname(hostname, CUSTOM_HOST_NAME_MAX) == 0)
		print_flag(ctx, hostname);
}


/*
** TTY name flag
*/

static void	l_flag(t_ctx *ctx)
{
	char *s;

	s = NULL;
	if (isatty(STDIN_FILENO) && (s = ttyname(STDIN_FILENO)) && (s = ft_basename(s)))
		print_flag(ctx, s);
	free(s);
}

/*
** Executable name flag
*/

static void	s_flag(t_ctx *ctx)
{
	size_t	len;
	char	*c;

	if ((c = ft_strrchr(ctx->av[0], '/')))
	{
			len = ft_strlen(c + 1);
			write(STDOUT_FILENO, c + 1, len);
	}
	else
	{
		len = ft_strlen(ctx->av[0]);
		write(STDOUT_FILENO, ctx->av[0], len);
	}
	ctx->cur_line->cursor_offset += len;
}

/*
** Username flag
*/

static void	u_flag(t_ctx *ctx)
{
	struct passwd *pw;

	if ((pw = getpwuid(getuid())))
		print_flag(ctx, pw->pw_name);
}

/*
** Fullpath Current directory flag
*/

static void	w_flag(t_ctx *ctx)
{
	char *cwd;
	char *homedir;
	char *tmp;

	homedir = ft_astr_getval(ctx->environ, "HOME");
	cwd = getcwd(NULL, 0);
	if (cwd && homedir && (tmp = ft_strstr(cwd, homedir)) && tmp == cwd && cwd[ft_strlen(homedir)] == '/')
	{
		ctx->cur_line->cursor_offset += ft_strlen(cwd) - ft_strlen(homedir) + 1;
		write(STDOUT_FILENO, "~", 1);
		ft_putstr(cwd + ft_strlen(homedir));
	}
	else if (cwd)
		print_flag(ctx, cwd);
	free(cwd);
}

/*
** Current directory flag
*/

static void	cap_w_flag(t_ctx *ctx)
{
	char *cwd;
	char *basename_cwd;

	if ((cwd = getcwd(NULL, 0)) && (basename_cwd = ft_basename(cwd)))
	{
		print_flag(ctx, basename_cwd);
		free(basename_cwd);
	}
	free(cwd);
}

static void	bang_flag(t_ctx *ctx)
{
	char *histnum;

	histnum = ft_itoa(ctx->hist.index);
	if (histnum)
		print_flag(ctx, histnum);
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

void	print_prompt(void)
{
	t_ctx			*ctx;
	t_prompt_flag	flags[9];
	char			*prompt;
	int				i;
	char			c;

	ctx = get_ctxaddr();
	if (!ctx->istty || !(prompt = ft_astr_getval(ctx->locals, ctx->prompt_mode)))
		return ;
	i = 0;
	init_flags(flags);
	while (*prompt)
	{
		if (*prompt == '\\' && (c = ispromptflag(*(prompt + 1))))
		{
			while (flags[i].flag != c)
				i++;
			flags[i].func(ctx);
			prompt++;
		}
		else
		{
			ctx->cur_line->cursor_offset++;
			write(STDOUT_FILENO, prompt, 1);
		}
		if (!(ctx->cur_line->cursor_offset % ctx->ws.ws_col))
			tputs(ctx->tc.dow, 1, &ft_putchar_stdin);
		prompt++;
	}
}
