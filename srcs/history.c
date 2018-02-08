/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 13:39:52 by lportay           #+#    #+#             */
/*   Updated: 2018/02/08 20:03:59 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*get_histfile(t_ctx *ctx)
{
	char	*path_to_file;

	if (!(path_to_file = ft_astr_getval(ctx->environ, "HOME")))
		ctx->hist.file = open(HISTFILE, O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
	else
		ctx->hist.file = open((path_to_file = fullpath(path_to_file, HISTFILE)), O_CREAT | O_RDWR,
		S_IWUSR | S_IRUSR);
	if (ctx->hist.file == -1)
		ctx->history = false;
	if (path_to_file)
		return (path_to_file);
	else if (ctx->history == true)
		return (ft_strdup(HISTFILE));
	else
		return ("");
}

t_histentry		*new_histentry(t_dlist *line, unsigned index)
{
	t_histentry *he;

	if (!(he = (t_histentry *)malloc(sizeof(t_histentry))))
		return (NULL);
	he->line = line;
	he->index = index;
	return (he);
}

void	del_histentry(void *histentry, size_t histentry_size)
{
	(void)histentry_size;
//	ft_dlsthead(&T_HISTENTRY(histentry)->line);//
	ft_dlstdel(&T_HISTENTRY(histentry)->line, &delvoid);
	ft_memdel(&histentry);
}

/*
** Imprimer dans le bon sens pour le built-in `history'
*/

//
void	dump_history(t_dlist *histlist)
{
	while (histlist)
	{
		ft_putnbr(T_HISTENTRY(histlist->data)->index);
		write(STDOUT_FILENO, "  ", 2);
		ft_dlstprint(T_HISTENTRY(histlist->data)->line->next, "", (void (*)(void *))&ft_putstr);
		write(STDOUT_FILENO, "\n", 2);
		histlist = histlist->next;
	}
}

void	trim_history(t_dlist **histlist, char *s_histsize)
{
	int		histsize;
	t_dlist	*tmp;

	if (s_histsize)
		histsize = ft_atoi(s_histsize);
	else
		histsize = ft_atoi(HISTSIZE);
	tmp = *histlist;
	while (histsize && *histlist)
	{
		*histlist = (*histlist)->next;
		histsize--;
	}
	if (*histlist)
	{
		(*histlist)->prev->next = NULL;
		ft_dlstdel(histlist, &del_histentry);
	}
	*histlist = tmp;
}

void	save_history(char **locals, t_dlist *histlist)
{
	char	*tmp;
	int		histfile;

	if ((tmp = ft_astr_getval(locals, "HISTFILE")))
		histfile = open(tmp, O_CREAT | O_TRUNC | O_RDWR, S_IWUSR | S_IRUSR);
	else
		histfile = open(HISTFILE, O_CREAT | O_TRUNC | O_RDWR, S_IWUSR | S_IRUSR);
	if (histfile == -1)
		return ;

	ft_dlstend(&histlist);
	while (histlist->prev)
	{
		tmp = dlst_to_str(T_HISTENTRY(histlist->data)->line);
		if (tmp && !str_isblank(tmp))
		{
			write(histfile, tmp, ft_strlen(tmp));
			write(histfile, "\n", 1);
		}
		ft_strdel(&tmp);
		histlist = histlist->prev;
	}
	close(histfile);
}

void	add_histentry(t_ctx *ctx)
{
		ft_dlstinsert(ctx->hist.list, ft_dlstnewaddr(new_histentry(ctx->line.split_line, ctx->hist.index++), sizeof(t_histentry)));
		trim_history(&ctx->hist.list->next, ft_astr_getval(ctx->locals, "HISTSIZE"));
}

void	init_hist(t_ctx *ctx)
{
	char	*histentry;

	if (get_next_line(ctx->hist.file, &histentry) == -1)
	{
		ctx->history = false;
		close(ctx->hist.file);
		return ;
	}
	while (histentry)
	{
		if (ft_strlen(histentry))
				ft_dlstadd(&ctx->hist.list, ft_dlstnewaddr(new_histentry(str_to_dlst(histentry), ctx->hist.index++), sizeof(t_histentry)));
			free(histentry);
		if (get_next_line(ctx->hist.file, &histentry) == -1)
		{
			close(ctx->hist.file);
			ft_dlstdel(&ctx->hist.list, &del_histentry);
			ctx->history = false;
			return ;
		}
	}
	close(ctx->hist.file);
	trim_history(&ctx->hist.list, ft_astr_getval(ctx->locals, "HISTSIZE"));
	ft_dlstadd(&ctx->hist.list, ft_dlstnew("HEAD", 4));
}
