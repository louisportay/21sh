/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 19:18:10 by lportay           #+#    #+#             */
/*   Updated: 2018/03/14 16:57:56 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
** Return the flag is 'c' is one
*/

static char	ispromptflag(char c)
{
	if (c == 'd' || c == 'H' || c == 'l' || c == 's' || c == 'u' || c == 'w' ||
			c == 'W' || c == '!')
		return (c);
	return (0);
}

static void	init_flags(t_prompt_flag *flags)
{
	flags[0] = (t_prompt_flag){.fun = &d_flag, .flag = 'd'};
	flags[1] = (t_prompt_flag){.fun = &cap_h_flag, .flag = 'H'};
	flags[2] = (t_prompt_flag){.fun = &l_flag, .flag = 'l'};
	flags[3] = (t_prompt_flag){.fun = &s_flag, .flag = 's'};
	flags[4] = (t_prompt_flag){.fun = &u_flag, .flag = 'u'};
	flags[5] = (t_prompt_flag){.fun = &w_flag, .flag = 'w'};
	flags[6] = (t_prompt_flag){.fun = &cap_w_flag, .flag = 'W'};
	flags[7] = (t_prompt_flag){.fun = &bang_flag, .flag = '!'};
	flags[8] = (t_prompt_flag){.fun = NULL, .flag = 0};
}

static void	get_flag(t_ctx *ctx, t_prompt_flag *fl, char **prompt, char c)
{
	int		i;

	i = 0;
	while (fl[i].flag != c)
		i++;
	fl[i].fun(ctx);
	(*prompt)++;
}

static void	print_char(t_ctx *ctx, char *prompt)
{
	ctx->cur_line->prompt_len += write(STDERR_FILENO, prompt, 1);
	if (*prompt == '\n')
	{
		ctx->cur_line->prompt_len = 0;
		ctx->cur_line->num_lines++;
	}
	if (!(ctx->cur_line->prompt_len % ctx->ws.ws_col)
			&& ctx->cur_line->prompt_len > 0)
	{
		tputs(ctx->tc.dow, 1, &ft_putchar_stdin);
		ctx->cur_line->num_lines++;
	}
}

void		print_prompt(void)
{
	t_ctx			*ctx;
	t_prompt_flag	flags[9];
	char			*prompt;
	char			c;

	ctx = get_ctxaddr();
	ctx->cur_line->prompt_len = 0;
	ctx->cur_line->num_lines = 0;
	if (!ctx->istty ||
			!(prompt = ft_astr_getval(ctx->locals, ctx->prompt_mode)))
		return ;
	init_flags(flags);
	while (*prompt)
	{
		if (*prompt == '\\' && (c = ispromptflag(*(prompt + 1))))
			get_flag(ctx, flags, &prompt, c);
		else
			print_char(ctx, prompt);
		prompt++;
	}
}
