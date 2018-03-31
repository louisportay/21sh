/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 11:37:11 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/31 16:34:55 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int			lp(char *path)
{
	ft_printf("%s\n", path);
	return (0);
}

static int			l_cd(t_ctx *ctx, char *path, int prt)
{
	char			cwd[MAXPATHLEN + 1];
	struct stat		stats;

	getcwd(cwd, MAXPATHLEN + 1);
	if (chdir(path) != 0)
	{
		if (stat(path, &stats) == -1)
		{
			ft_dprintf(STDERR_FILENO, "21sh: cd: %s: %s\n", path, SH_ENOFOD);
			return (1);
		}
		else if (access(path, X_OK) == -1)
		{
			ft_dprintf(STDERR_FILENO, "21sh: cd: %s: %s\n", path, SH_ERIGHT);
			return (1);
		}
	}
	astr_env_replace(&ctx->environ, "OLDPWD", cwd);
	getcwd(cwd, MAXPATHLEN + 1);
	astr_env_replace(&ctx->environ, "PWD", cwd);
	return (prt ? lp(cwd) : 0);
}

static int			lcd_tar(t_ctx *ctx, char *key, char *err)
{
	char			*str;

	if ((str = ft_astr_getval(ctx->environ, key)) == NULL)
	{
		ft_putstr_fd(err + 1, STDERR_FILENO);
		return (1);
	}
	return (l_cd(ctx, str, ft_strcmp(key, "HOME")));
}

int					ft_cd(t_proc *p, t_ctx *ctx)
{
	p->type = BU_STR;
	if (ft_astr_len(p->argv) > 2)
	{
		ft_putstr_fd(SH_EARGTO + 1, STDERR_FILENO);
		return (1);
	}
	if (p->argv[1] == NULL)
		return (lcd_tar(ctx, "HOME", SH_ENOHOM));
	else if (ft_strcmp("-", p->argv[1]) == 0)
		return (lcd_tar(ctx, "OLDPWD", SH_ENOOPW));
	return (l_cd(ctx, p->argv[1], 0));
}
