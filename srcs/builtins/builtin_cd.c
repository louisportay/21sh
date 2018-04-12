/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 11:37:11 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/12 12:52:39 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int			remove_prev_dir(char *trim_path, unsigned *i, char *argpath)
{
	struct stat	st;

	if (*i > 1 && trim_path[*i - 1] == '/')
		trim_path[--(*i)] = '\0';
	if (stat(trim_path, &st) == -1)
	{
		ft_dprintf(STDERR_FILENO, "21sh: cd: %s: %s\n", argpath, SH_ENOFOD);
		return (-1);
	}
	else if (!S_ISDIR(st.st_mode))
	{
		ft_dprintf(STDERR_FILENO, "21sh: cd: %s: %s\n", argpath, SH_ENODIR);
		return (-1);
	}
	while (*i != 0 && trim_path[*i - 1] != '/')
		trim_path[--(*i)] = '\0';
	return (0);
}

static void	cd_getopt(char **operand, char *opt, char **av)
{
	*operand = av[1];
	*opt = 0;
	if (ft_astr_len(av) == 3)
	{
		*operand = av[2];
		if (av[1][1] == 'P')
			*opt |= 1;
	}
}

static int	cd_special_operand(char **operand, char *opt, char **environ,
									char **locals)
{
	if (*operand == NULL)
	{
		if ((*operand = ft_astr_getval(environ, "HOME")) == NULL
				&& (*operand = ft_astr_getval(locals, "HOME")) == NULL)
		{
			ft_putstr_fd(SH_ENOHOM, STDERR_FILENO);
			return (1);
		}
	}
	else if (!ft_strcmp(*operand, "-"))
	{
		if ((*operand = ft_astr_getval(environ, "OLDPWD")) == NULL
				&& (*operand = ft_astr_getval(locals, "OLDPWD")) == NULL)
		{
			ft_putstr_fd(SH_ENOOPW, STDERR_FILENO);
			return (1);
		}
		*opt |= 2;
	}
	return (0);
}

int			ft_cd(t_proc *p, t_ctx *ctx)
{
	char *operand;
	char opt;

	p->type = BUILTIN;
	if (ft_astr_len(p->argv) > 3 || (ft_astr_len(p->argv) == 3 &&
	ft_strcmp(p->argv[1], "-P") && ft_strcmp(p->argv[1], "-L")))
	{
		ft_putstr_fd(SH_EARGTO, STDERR_FILENO);
		return (1);
	}
	cd_getopt(&operand, &opt, p->argv);
	if (cd_special_operand(&operand, &opt, ctx->environ, ctx->locals) == 1)
		return (1);
	if (ft_strlen(operand) >= MAXPATHLEN)
	{
		ft_dprintf(STDERR_FILENO,
				"21sh: cd: %s: File name too long\n", operand);
		return (1);
	}
	return (cd_pipeline(ctx, operand, opt));
}
