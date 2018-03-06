/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 13:39:52 by lportay           #+#    #+#             */
/*   Updated: 2018/03/06 18:11:06 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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
	ft_dlstdel(&T_HISTENTRY(histentry)->line, &delvoid);
	ft_memdel(&histentry);
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

void	save_history(char *histfile, t_dlist *histlist)
{
	char	*tmp;
	int		fd;

	if (histfile)
		fd = open(histfile, O_CREAT | O_TRUNC | O_RDWR, S_IWUSR | S_IRUSR);
	else
		fd = open(HISTFILE, O_CREAT | O_TRUNC | O_RDWR, S_IWUSR | S_IRUSR);
	if (fd == -1)
		return ;

	ft_dlstend(&histlist);
	while (histlist->prev)
	{
		tmp = dlst_to_str(T_HISTENTRY(histlist->data)->line);
		if (tmp && !str_isblank(tmp))
		{
			write(fd, tmp, ft_strlen(tmp));
			write(fd, "\n", 1);
		}
		ft_strdel(&tmp);
		histlist = histlist->prev;
	}
	close(fd);
}

void	add_histentry(t_hist *hist, t_dlist *line)
{
	ft_dlstinsert(hist->list, ft_dlstnewaddr(new_histentry(ft_dlstdup(line), hist->index++), sizeof(t_histentry)));
	trim_history(&hist->list->next, ft_astr_getval(get_ctxaddr()->locals, "HISTSIZE"));
}

void	init_hist(t_hist *hist)
{
	char	*histentry;
	int		file;
 	
	histentry = NULL;
	file = open(ft_astr_getval(get_ctxaddr()->locals, "HISTFILE"), O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);

	get_next_line(file, &histentry);

	while (histentry)
	{
		if (ft_strlen(histentry))
				ft_dlstadd(&hist->list, ft_dlstnewaddr(new_histentry(str_to_dlst(histentry), hist->index++), sizeof(t_histentry)));
			free(histentry);
		if (get_next_line(file, &histentry) == -1)
			break ;
	}

	close(file);
	trim_history(&hist->list, ft_astr_getval(get_ctxaddr()->locals, "HISTSIZE"));
	ft_dlstadd(&hist->list, ft_dlstnew("HEAD", 4));
}
