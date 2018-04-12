/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 13:23:20 by lportay           #+#    #+#             */
/*   Updated: 2018/04/12 17:25:04 by lportay          ###   ########.fr       */
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
	while (line->prev && ft_isblank(*(char *)line->data) == 0)
		line = line->prev;	
	if (line->next == NULL && ft_isblank(*(char *)line->data) == 1)
	{
			if ((s = ft_strdup("./")) == NULL)
				fatal_err(NOMEM, get_ctxaddr());
	}
	else if ((s = str_from_dlst(line)) == NULL)
		fatal_err(NOMEM, get_ctxaddr());
	line = tmp;
	line->next = next;
	return (s);
}

//int            string_has_blank(char *s)
//{
//	while (*s)
//		if (ft_isblank(*s++) == 1)
//			return (1);
//	return (0);
//}

int		dlst_hasblank(t_dlist *dlst)
{
	while (dlst->prev)
	{
		if (ft_isblank(*(char *)dlst->data) == 1)
			return (1);
		dlst = dlst->prev;
	}
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

void	complete_path(t_ctx *ctx, t_line *l, struct s_string str)
{
	DIR				*dp;
	struct dirent	*de;	
	t_dlist			*matches;
	char			*dirname;
	char			*basename;
	char			*last_slash;
	unsigned		maxlen;

	maxlen = 0;
	matches = NULL;
	basename = NULL;
	dirname = NULL;

	if ((last_slash = ft_strrchr(str.s, '/')) == NULL)
	{
		if ((dp = opendir(".")) == NULL)
			return ;
//		printf("\ndirname=%s\n", str.s);
	}
	else
	{
		dirname = ft_strdup(str.s);
		*(ft_strrchr(dirname, '/') + 1) = '\0';
		dp = opendir(dirname);
//		printf("\ndirname=%s\n", dirname);
		free(dirname);
	}
	

	if ((last_slash = ft_strrchr(str.s, '/')) == NULL)
		basename = ft_strdup(str.s);
	else
		basename = ft_strdup(last_slash + 1);

//	printf("s=%s\nbase=%s\n", str.s, basename);

	unsigned baselen;

	baselen = ft_strlen(basename);
	while ((de = readdir(dp)))
	{
		if (!ft_strncmp(basename, de->d_name, baselen))
		{
			if (!(baselen == 0
					&& (!ft_strcmp(".", de->d_name) || !ft_strcmp("..", de->d_name))))
			{
				unsigned len;
				len = ft_strlen(de->d_name);
				if (ft_dlstnewadd(&matches, de->d_name, len, &ft_dlstnew) == -1)
				{
					ft_dlstdel(&matches, &delvoid);
					fatal_err(NOMEM, get_ctxaddr());
				}
				if (len > maxlen)
					maxlen = len;
//				printf("MATCH=%s\n", de->d_name);
			}
		}
	}
	closedir(dp);
	if (!matches)
		return (free(basename));
	else if (matches->next)
		print_results(matches, ((maxlen / PAD) + 1) * PAD, ctx->ws.ws_col);
	else
	{
		//printf("%s\n", matches->data);
		if (ft_strcmp(basename, matches->data))
		{
			if (str.s[ft_strlen(str.s) - 1] == '/')
				dirname = ft_strjoin(str.s, matches->data);
			else
				dirname = ft_strjoinc(str.s, matches->data, '/');
		}
		if ((dp = opendir(dirname)))
		{
			closedir(dp);
			printf("\n|%s|\n", dirname);
			printf("\n|%s|\n", str.s);
			free(matches->data);
			matches->data = ft_strnew(ft_strlen(dirname + 1));
		//	ft_memcpy(matches->data, dirname, ft_strlen(dirname));
		//	ft_memcpy(matches->data, "/", 1);
			printf("\n|%s|\n", (char *)matches->data);
			complete_line(l, matches->data, baselen);
		}
		else if (ft_strcmp(basename, matches->data))
		{
			complete_line(l, matches->data, baselen);
			free(dirname);
		}
	}
	ft_dlstdel(&matches, &delvoid);
	restore_line(ctx, l);
	free(basename);
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

	if (dlst_hasblank(l->line) == 1)	
		complete_path(ctx, l, str);
	else
		complete_binary(ctx, l, ctx->path, str);
	free(str.s);
}
