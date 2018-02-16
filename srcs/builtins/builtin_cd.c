/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 11:37:11 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/16 20:25:44 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int			l_cd(t_proc *p, t_ctx *ctx, char *path)
{
	char			cwd[MAXPATHLEN + 1];
	struct stat		stats;
	
	getcwd(cwd, MAXPATHLEN + 1);
	if (chdir(path) != 0)
	{
		if (stat(path, &stats) == -1)
		{
			p->data.out = list_create(ft_strdup(SH_ENOFOD));
			return (1);
		}
		else if (access(path, X_OK) == -1)
		{
			p->data.out = list_create(ft_strdup(SH_ERIGHT));
			return (1);
		}
	}
	astr_env_replace(&ctx->environ, "OLDPWD", ft_strdup(cwd));
	getcwd(cwd, MAXPATHLEN + 1);
	astr_env_replace(&ctx->environ, "PWD", ft_strdup(cwd));
	return (0);
}

static int			lcd_tar(t_proc *p, t_ctx *ctx, char *key, char *err)
{
	char			*str;

	if ((str = ft_astr_getval(ctx->environ, key)) == NULL)
	{
		p->data.out = list_create(ft_strdup(err));
		return (1);
	}
	return (l_cd(p, ctx, str));
}

int					ft_cd(t_proc *p, t_ctx *ctx)
{
	p->type = BUILTIN;
	if (ft_astr_len(p->argv) > 2)
	{
		p->data.out = list_create(ft_strdup(SH_EARGTO));
		return (1);
	}
	if (p->argv[1] == NULL)
		return (lcd_tar(p, ctx, "HOME", SH_ENOHOM));
	else if (ft_strcmp("-", p->argv[1]) == 0)
		return (lcd_tar(p, ctx, "OLDPWD", SH_ENOOPW));
	return (l_cd(p, ctx, p->argv[1]));
}
