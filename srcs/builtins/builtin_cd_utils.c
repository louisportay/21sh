/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 19:24:29 by lportay           #+#    #+#             */
/*   Updated: 2018/04/07 10:44:25 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char		*trim_path(char *path, char *argpath)
{
	char			trim_path[MAXPATHLEN + 1];
	unsigned		i;

	i = 0;
	ft_bzero(trim_path, MAXPATHLEN + 1);
	while (*path)
	{
		if ((*path == '/' && i != 0 && (trim_path[i - 1] == '/')) ||
		((!ft_strncmp(path, "./", 2) || !ft_strcmp(path, ".")) &&
		(trim_path[i - 1] == '/')))
			;
		else if ((!ft_strncmp(path, "../", 3) || !ft_strcmp(path, "..")) &&
				(trim_path[i - 1] == '/'))
		{
			if (remove_prev_dir(trim_path, &i, argpath) == -1)
				return (NULL);
			path++;
		}
		else
			trim_path[i++] = *path;
		path++;
	}
	if (i > 1 && trim_path[i - 1] == '/')
		trim_path[--i] = '\0';
	return (ft_strdup(trim_path));
}

static char		*get_cur_path(char **environ, char *path)
{
	char	*prefix;
	char	*curpath;
	int		alloc;

	if (path[0] == '/')
		curpath = ft_strdup(path);
	else
	{
		alloc = 0;
		if (!(prefix = ft_astr_getval(environ, "PWD")))
		{
			prefix = getcwd(NULL, 0);
			alloc = 1;
		}
		if (prefix[ft_strlen(prefix) - 1] == '/')
			curpath = ft_strjoin(prefix, path);
		else
			curpath = ft_strjoinc(prefix, path, '/');
		if (alloc == 1)
			free(prefix);
	}
	return (curpath);
}

static int		chdir_print_err(char *newpath, char *argpath)
{
	struct stat st;

	if (chdir(newpath) != 0)
	{
		if (stat(newpath, &st) == -1)
		{
			ft_dprintf(STDERR_FILENO, "21sh: cd: %s: %s\n", argpath, SH_ENOFOD);
			return (1);
		}
		else if (!S_ISDIR(st.st_mode))
		{
			ft_dprintf(STDERR_FILENO, "21sh: cd: %s: %s\n", argpath, SH_ENODIR);
			return (1);
		}
		else if (access(newpath, X_OK) == -1)
		{
			ft_dprintf(STDERR_FILENO, "21sh: cd: %s: %s\n", argpath, SH_ERIGHT);
			return (1);
		}
	}
	return (0);
}

static void		set_pwd_vars(char ***environ, int opt, char *newpath)
{
	char			cwd[MAXPATHLEN + 1];

	astr_env_replace(environ, "OLDPWD", ft_astr_getval(*environ, "PWD"));
	if (opt & 1)
	{
		getcwd(cwd, MAXPATHLEN + 1);
		astr_env_replace(environ, "PWD", cwd);
	}
	else
		astr_env_replace(environ, "PWD", newpath);
}

int				cd_pipeline(t_ctx *ctx, char *path, int opt)
{
	char	*curpath;
	char	*newpath;

	curpath = get_cur_path(ctx->environ, path);
	if (opt & 1)
		newpath = curpath;
	else if ((newpath = trim_path(curpath, path)) == NULL)
	{
		free(curpath);
		return (1);
	}
	if (chdir_print_err(newpath, path) != 0)
	{
		free(curpath);
		if (newpath != curpath)
			free(newpath);
		return (1);
	}
	set_pwd_vars(&ctx->environ, opt, newpath);
	if (opt & 2)
		ft_printf("%s\n", curpath);
	free(curpath);
	if (newpath != curpath)
		free(newpath);
	return (0);
}
