/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_flags1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 12:57:13 by lportay           #+#    #+#             */
/*   Updated: 2018/03/14 13:35:25 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Date flag
*/

void	d_flag(t_ctx *ctx)
{
	char		*time_str;
	struct tm	*tm;
	time_t		t;

	t = time(NULL);
	tm = localtime(&t);
	time_str = asctime(tm);
	time_str[10] = '\0';
	print_flag(ctx, time_str);
}

/*
** Hostname flag (not truncated)
*/

void	cap_h_flag(t_ctx *ctx)
{
	char	hostname[CUSTOM_HOST_NAME_MAX];

	if (gethostname(hostname, CUSTOM_HOST_NAME_MAX) == 0)
		print_flag(ctx, hostname);
}

/*
** TTY name flag
*/

void	l_flag(t_ctx *ctx)
{
	char *s;

	s = NULL;
	if (isatty(STDIN_FILENO) && (s = ttyname(STDIN_FILENO)) &&
			(s = ft_basename(s)))
		print_flag(ctx, s);
	free(s);
}

/*
** Executable name flag
*/

void	s_flag(t_ctx *ctx)
{
	char	*c;

	if ((c = ft_strrchr(ctx->av[0], '/')))
		print_flag(ctx, c + 1);
	else
		print_flag(ctx, ctx->av[0]);
}

/*
** Username flag
*/

void	u_flag(t_ctx *ctx)
{
	struct passwd *pw;

	if ((pw = getpwuid(getuid())))
		print_flag(ctx, pw->pw_name);
}
