/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_binary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 20:33:31 by lportay           #+#    #+#             */
/*   Updated: 2018/04/12 20:47:58 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	fill_matches_binary(t_string str, struct dirent *de,
						t_dlist **matches, unsigned *maxlen)
{
	unsigned		len;

	if (ft_strncmp(str.s, de->d_name, str.len) == 0
			&& entry_already_in_list(de->d_name, *matches) == 0)
	{
		len = ft_strlen(de->d_name);
		if (ft_dlstnewadd(matches, de->d_name, len, &ft_dlstnew) == -1)
		{
			ft_dlstdel(matches, &delvoid);
			fatal_err(NOMEM, get_ctxaddr());
		}
		if (len > *maxlen)
			*maxlen = len;
	}
}

void		complete_binary(t_ctx *ctx, t_line *l, char **p, t_string str)
{
	DIR				*dp;
	struct dirent	*de;	
	t_dlist			*matches;
	unsigned		maxlen;

	if (p == NULL)
		return ;
	maxlen = 0;
	matches = NULL;
	while (*p)
	{
		dp = opendir(*p);
		while ((de = readdir(dp)))
			fill_matches_binary(str, de, &matches, &maxlen);
		closedir(dp);
		p++;
	}
	if (!matches)
		return ;
	else if (matches->next)
		print_results(matches, ((maxlen / PAD) + 1) * PAD, ctx->ws.ws_col);
	else if (ft_strcmp(str.s, matches->data))
		complete_line(l, matches->data, str.len);
	restore_line(ctx, l);
	ft_dlstdel(&matches, &delvoid);
}
