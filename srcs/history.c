/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 13:39:52 by lportay           #+#    #+#             */
/*   Updated: 2018/01/27 17:22:52 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*get_histfile(t_21sh *env)
{
	char	*path;

	if (!(path = get_kvp("HOME", env->environ)))
		env->hist.file = open(HISTFILE, O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
	else
		env->hist.file = open((path = fullpath(path, HISTFILE)), O_CREAT | O_RDWR,
		S_IWUSR | S_IRUSR);

	if (env->hist.file == -1)
		env->history = false;

	if (path)
		return (path);
	else if (env->history == true)
		return (ft_strdup(HISTFILE));
	else
		return (NULL);
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

void	del_histentry(void *histentry, size_t histentrysize)
{
	(void)histentrysize;
//	ft_dlsthead(&T_HISTENTRY(histentry)->line);//
	ft_dlstdel(&T_HISTENTRY(histentry)->line, &delvoid);
	free(histentry);

}

/*
** Imprimer dans le bon sens pour le built-in `history'
*/

//
void	dump_history(t_dlist *histlist)
{
	while (histlist)
	{
		ft_putnbr(T_HISTENTRY(histlist->content)->index);
		write(STDOUT_FILENO, "  ", 2);
		ft_dlstprint(T_HISTENTRY(histlist->content)->line->next, "");
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
		(*histlist)->previous->next = NULL;
		ft_dlstdel(histlist, &del_histentry);
	}
	*histlist = tmp;
}

void	save_history(t_kvp *local, t_dlist *histlist)
{
	char	*tmp;
	int		histfile;

	if ((tmp = get_kvp("HISTFILE", local)))
		histfile = open(tmp, O_CREAT | O_TRUNC | O_RDWR, S_IWUSR | S_IRUSR);
	else
		histfile = open(HISTFILE, O_CREAT | O_TRUNC | O_RDWR, S_IWUSR | S_IRUSR);
	if (histfile == -1)
		return ;

	ft_dlstend(&histlist);
	while (histlist->previous)
	{
		tmp = dlst_to_str(T_HISTENTRY(histlist->content)->line);
		if (tmp && !str_isblank(tmp))
		{
			write(histfile, tmp, ft_strlen(tmp));
			write(histfile, "\n", 1);
		}
		ft_strdel(&tmp);
		histlist = histlist->previous;
	}
	close(histfile);
}

void	add_histentry(t_21sh *env)
{
		ft_dlstinsert(env->hist.list, ft_dlstnewaddr(new_histentry(env->line.split_line, env->hist.index++), sizeof(t_histentry *)));
		trim_history(&env->hist.list->next, get_kvp("HISTSIZE", env->local));
}

void	init_hist(t_21sh *env)
{
	char	*histentry;

	if (get_next_line(env->hist.file, &histentry) == -1)
	{
		env->history = false;
		close(env->hist.file);
		return ;
	}
	while (histentry)
	{
		if (ft_strlen(histentry))
				ft_dlstadd(&env->hist.list, ft_dlstnewaddr(new_histentry(str_to_dlst(histentry), env->hist.index++), sizeof(t_histentry *)));
			free(histentry);
		if (get_next_line(env->hist.file, &histentry) == -1)
		{
			close(env->hist.file);
			ft_dlstdel(&env->hist.list, &del_histentry);
			env->history = false;
			return ;
		}
	}
	close(env->hist.file);
	trim_history(&env->hist.list, get_kvp("HISTSIZE", env->local));
	ft_dlstadd(&env->hist.list, ft_dlstnew("HEAD", 5));
}
