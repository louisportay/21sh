/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 20:30:18 by lportay           #+#    #+#             */
/*   Updated: 2018/04/13 10:58:46 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static DIR		*get_dirp(t_string str)
{
	DIR		*dp;
	char	*dirname;

	if (!(ft_strrchr(str.s, '/')))
		dp = opendir(".");
	else
	{
		dirname = ft_strdup(str.s);
		*(ft_strrchr(dirname, '/') + 1) = '\0';
		dp = opendir(dirname);
		free(dirname);
	}
	return (dp);
}

static void		fill_matches_path(t_string basename, struct dirent *de,
		t_dlist **matches, unsigned *maxlen)
{
	unsigned len;

	if (!ft_strncmp(basename.s, de->d_name, basename.len)
		&& (!(basename.len == 0 && (!ft_strcmp(".", de->d_name)
					|| !ft_strcmp("..", de->d_name)))))
	{
		len = ft_strlen(de->d_name);
		if (de->d_type & DT_DIR)
		{
			if (ft_dlstnewadd(matches, ft_strjoin(de->d_name, "/"), len++,
						&ft_dlstnewaddr) == -1)
			{
				ft_dlstdel(matches, &delvoid);
				fatal_err(NOMEM, get_ctxaddr());
			}
		}
		else if (ft_dlstnewadd(matches, de->d_name, len, &ft_dlstnew) == -1)
		{
			ft_dlstdel(matches, &delvoid);
			fatal_err(NOMEM, get_ctxaddr());
		}
		if (len > *maxlen)
			*maxlen = len;
	}
}

static t_string	get_basename(char *s)
{
	t_string		basename;
	char			*last_slash;

	if ((last_slash = ft_strrchr(s, '/')) == NULL)
		basename.s = ft_strdup(s);
	else
		basename.s = ft_strdup(last_slash + 1);
	if (!basename.s)
		fatal_err(NOMEM, get_ctxaddr());
	basename.len = ft_strlen(basename.s);
	return (basename);
}

void			complete_path(t_ctx *ctx, t_line *l, t_string str)
{
	t_string		basename;
	DIR				*dp;
	struct dirent	*de;
	t_dlist			*matches;
	unsigned		maxlen;

	maxlen = 0;
	matches = NULL;
	if (!(dp = get_dirp(str)))
		return ;
	basename = get_basename(str.s);
	while ((de = readdir(dp)))
		fill_matches_path(basename, de, &matches, &maxlen);
	closedir(dp);
	if (!matches)
		return (free(basename.s));
	else if (matches->next)
		print_results(matches, ((maxlen / PAD) + 1) * PAD, ctx->ws.ws_col);
	else if (ft_strcmp(basename.s, matches->data))
		complete_line(l, matches->data, basename.len);
	restore_line(ctx, l);
	ft_dlstdel(&matches, &delvoid);
	free(basename.s);
}
