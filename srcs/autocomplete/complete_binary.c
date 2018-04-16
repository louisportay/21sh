/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_binary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 20:33:31 by lportay           #+#    #+#             */
/*   Updated: 2018/04/13 14:10:19 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int	fill_matches_binary(t_string str, char *path, struct dirent *de,
															t_dlist **matches)
{
	unsigned		len;
	char			fpath[PATH_MAX + 1];

	if (ft_strlen(path) + ft_strlen(de->d_name) >= PATH_MAX)
		return (0);
	ft_bzero(fpath, PATH_MAX + 1);
	ft_strcat(fpath, path);
	ft_strcat(fpath, "/");
	ft_strcat(fpath, de->d_name);
	len = 0;
	if (ft_strncmp(str.s, de->d_name, str.len) == 0 && !(de->d_type & DT_DIR)
	&& !access(fpath, X_OK) && !entry_already_in_list(de->d_name, *matches))
	{
		len = ft_strlen(de->d_name);
		if (ft_dlstnewadd(matches, de->d_name, len, &ft_dlstnew) == -1)
		{
			ft_dlstdel(matches, &delvoid);
			fatal_err(NOMEM, get_ctxaddr());
		}
	}
	return (len);
}

void		read_pathes(char *path, t_string str, t_dlist **matches,
								unsigned *maxlen)
{
	DIR				*dp;
	struct dirent	*de;
	unsigned		len;

	dp = opendir(path);
	while ((de = readdir(dp)))
	{
		len = fill_matches_binary(str, path, de, matches);
		if (len > *maxlen)
			*maxlen = len;
	}
	closedir(dp);
}

void		complete_binary(t_ctx *ctx, t_line *l, char **p, t_string str)
{
	t_dlist			*matches;
	unsigned		maxlen;

	if (p == NULL)
		return ;
	maxlen = 0;
	matches = NULL;
	while (*p)
		read_pathes(*p++, str, &matches, &maxlen);
	if (!matches)
		return ;
	else if (matches->next)
		print_results(ctx, l, matches, ((maxlen / PAD) + 1) * PAD);
	else if (ft_strcmp(str.s, matches->data))
		complete_line(ctx, l, matches->data, str.len);
	ft_dlstdel(&matches, &delvoid);
}
