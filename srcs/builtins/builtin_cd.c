/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 11:37:11 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/26 15:49:37 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int			lp(t_proc *p, char *path)
{
	char			*str;

	ft_asprintf(&str, "1%s\n", path);
	p->data.str = str;
	return (0);
}

static int			l_cd(t_proc *p, t_ctx *ctx, char *path, int prt)
{
	char			cwd[MAXPATHLEN + 1];
	struct stat		stats;
	char			*str;

	getcwd(cwd, MAXPATHLEN + 1);
	if (chdir(path) != 0)
	{
		if (stat(path, &stats) == -1)
		{
			ft_asprintf(&str, "221sh: cd: %s: %s\n", path, SH_ENOFOD);
			p->data.str = str;
			return (1);
		}
		else if (access(path, X_OK) == -1)
		{
			ft_asprintf(&str, "221sh: cd: %s: %s\n", path, SH_ERIGHT);
			p->data.str = str;
			return (1);
		}
	}
	astr_env_replace(&ctx->environ, "OLDPWD", cwd);
	getcwd(cwd, MAXPATHLEN + 1);
	astr_env_replace(&ctx->environ, "PWD", cwd);
	return (prt ? lp(p, cwd) : 0);
}

static int			lcd_tar(t_proc *p, t_ctx *ctx, char *key, char *err)
{
	char			*str;

	if ((str = ft_astr_getval(ctx->environ, key)) == NULL)
	{
		p->data.str = ft_strdup(err);
		return (1);
	}
	return (l_cd(p, ctx, str, ft_strcmp(key, "HOME")) == 0);
}

int					ft_cd(t_proc *p, t_ctx *ctx)
{
	p->type = BU_STR;
	if (ft_astr_len(p->argv) > 2)
	{
		p->data.str = ft_strdup(SH_EARGTO);
		return (1);
	}
	if (p->argv[1] == NULL)
		return (lcd_tar(p, ctx, "HOME", SH_ENOHOM));
	else if (ft_strcmp("-", p->argv[1]) == 0)
		return (lcd_tar(p, ctx, "OLDPWD", SH_ENOOPW));
	return (l_cd(p, ctx, p->argv[1], 0));
}
