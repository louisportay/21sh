/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_flags2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 13:12:14 by lportay           #+#    #+#             */
/*   Updated: 2018/03/14 13:36:23 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Fullpath Current directory flag
*/

void	w_flag(t_ctx *ctx)
{
	char *cwd;
	char *homedir;
	char *tmp;

	homedir = ft_astr_getval(ctx->environ, "HOME");
	cwd = getcwd(NULL, 0);
	if (cwd && homedir && (tmp = ft_strstr(cwd, homedir)) && tmp == cwd
			&& cwd[ft_strlen(homedir)] == '/')
	{
		ctx->cur_line->prompt_len += ft_strlen(cwd) - ft_strlen(homedir) + 1;
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

void	cap_w_flag(t_ctx *ctx)
{
	char *cwd;
	char *basename_cwd;

	if ((cwd = getcwd(NULL, 0)) &&
			(basename_cwd = ft_basename(cwd)))
	{
		print_flag(ctx, basename_cwd);
		free(basename_cwd);
	}
	free(cwd);
}

/*
** Hist index
*/

void	bang_flag(t_ctx *ctx)
{
	char *histnum;

	histnum = ft_itoa(ctx->hist.index);
	if (histnum)
		print_flag(ctx, histnum);
	free(histnum);
}
