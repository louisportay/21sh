/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 13:23:20 by lportay           #+#    #+#             */
/*   Updated: 2018/04/10 19:02:18 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

struct			s_string
{
	char		*s;
	unsigned	len;
};

char	*get_string_to_complete(t_dlist *line)
{
	t_dlist *tmp;
	t_dlist	*next;
	char	*s;

	next = line->next;
	line->next = NULL;
	tmp = line;
	ft_dlsthead(&line);	//recule jusqu'au debut OU au premier espace rencontre
	if ((s = str_from_dlst(line)) == NULL)
		fatal_err(NOMEM, get_ctxaddr());
	line = tmp;
	line->next = next;
	return (s);
}

int		string_has_blank(char *s)
{
	while (*s)
		if (ft_isblank(*s++) == 1)
			return (1);
	return (0);
}

int		entry_already_in_list(char *name, t_dlist *matches)
{
	while (matches)
	{
		if (ft_strcmp(name, (char *)matches->data) == 0)
			return (1);
		matches = matches->next;
	}
	return (0);
}

void	restore_line(t_ctx *ctx, t_line *l)
{
	t_dlist *tmp;

	tmp = l->line;
	clear_line(ctx, l);
	redraw_line(ctx, l);
	while (l->line != tmp)
		lkey(get_ctxaddr(), l);
}

void	print_results(t_dlist *matches, int maxlen, unsigned ws_col)
{
	int		entry_num;
	int		i;

	entry_num = ws_col / maxlen;
	i = 0;
	write(STDOUT_FILENO, "\n", 1);
	while (matches)
	{	
		ft_printf("%-*s", maxlen, (char *)matches->data);
		if (++i == entry_num)
		{
			write(STDOUT_FILENO, "\n", 1);
			i = 0;
		}
		matches = matches->next;
	}
	if (i != 0)
		write(STDOUT_FILENO, "\n", 1);
}

void	complete_line(t_line *l, char *fullpath, unsigned len)
{
	t_dlist *dlst;
	t_dlist *tmp;

	if((dlst = dlst_from_str(fullpath + len)) == NULL)
		fatal_err(NOMEM, get_ctxaddr());
	tmp = l->line->next;
	l->line->next = dlst->next;
	l->line->next->prev = l->line;
	ft_dlstend(&l->line);
	l->line->next = tmp;
	if (tmp)
		tmp->prev = l->line;	
	ft_dlstdelone(&dlst, &delvoid);
}


void	fill_matches(struct s_string str, struct dirent *de, t_dlist **matches, unsigned *maxlen)
{
	unsigned		len;

	if (ft_strncmp(str.s, de->d_name, str.len) == 0 && entry_already_in_list(de->d_name, *matches) == 0)
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

void	complete_binary(t_ctx *ctx, t_line *l, char **p, struct s_string str)
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
			fill_matches(str, de, &matches, &maxlen);
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

void	autocomplete(t_ctx *ctx, t_line *l)
{
	struct s_string str;

	str.s = get_string_to_complete(l->line);
	str.len = ft_strlen(str.s);

	if (str.len == 0 || str.len >= 4096)
		return (free(str.s));

	if (string_has_blank(str.s) == 1)	
	{
		//get_current_path_files
	}
	else
		complete_binary(ctx, l, ctx->path, str);
	free(str.s);
}
