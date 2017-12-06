/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 13:39:52 by lportay           #+#    #+#             */
/*   Updated: 2017/12/06 21:44:31 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		get_histfile(t_21sh *env)
{
	char	*path;
	t_hash	*tmp;

	if (!(path = ft_getenv("HOME", env->environ)))
		env->histfile = open(HISTFILE, O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
	else
		env->histfile = open((path = fullpath(path, HISTFILE)), O_CREAT | O_RDWR,
		S_IWUSR | S_IRUSR);
	if (env->histfile == -1)
		env->history = false;
	if (path)
	{
		if (!(tmp = hashaddr("HISTFILE", path, ft_strlen(path))))
			return (NOMEM);
		hashinsert(env->localvar, tmp, 0, &ft_memdel);
	}
	else if (env->history == true)
	{
		if (!(tmp = hashcreate("HISTFILE", HISTFILE, ft_strlen(HISTFILE))))
			return (NOMEM);
		hashinsert(env->localvar, tmp, 0, &ft_memdel);
	}
	return (SUCCESS);
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
	ft_dlsthead(&T_HISTENTRY(histentry)->line);//
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

void	trim_history(t_dlist **histlist, t_hash *histsizebucket)
{
	int		histsize;
	t_dlist	*tmp;

	if (!histsizebucket)
		histsize = ft_atoi(HISTSIZE);
	else
		histsize = ft_atoi((char *)histsizebucket->data);
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

void	save_history(t_hash **localvar, t_dlist *histlist)
{
	t_hash	*tmp;
	char	*s;
	int		histfile;
	int		histfilesize;

	if (!(tmp = hashlookup(localvar, "HISTFILE")))
		histfile = open(HISTFILE, O_CREAT | O_TRUNC | O_RDWR, S_IWUSR | S_IRUSR );
	else
		histfile = open((char *)tmp->data, O_CREAT | O_TRUNC | O_RDWR, S_IWUSR | S_IRUSR);
	if (histfile == -1)
		return ;
	if (!(tmp = hashlookup(localvar, "HISTFILESIZE")))
		histfilesize = ft_atoi(HISTFILESIZE);
	else
		histfilesize = ft_atoi((char *)tmp->data);
	ft_dlstend(&histlist);
	while (histlist->previous && histfilesize)
	{
		s = dlst_to_str(T_HISTENTRY(histlist->content)->line);
		if (s && isonlywhitespace(s) == false)
		{
			write(histfile, s, ft_strlen(s));
			write(histfile, "\n", 1);
			histfilesize--;
		}
		ft_strdel(&s);
		histlist = histlist->previous;
	}
	close(histfile);
}

void	init_hist(t_21sh *env)
{
	char				*histentry;

	while (histentry)
	{
		if (get_next_line(env->histfile, &histentry) == -1)
		{
			env->history = false;
			return ;
		}
		if (histentry)
		{
			if (ft_strcmp(histentry, "\0"))
				ft_dlstadd(&env->histlist, ft_dlstnewaddr(new_histentry(
		str_to_dlst(histentry), env->histindex++), sizeof(t_histentry *)));
			free(histentry);
		}
	}
	close(env->histfile);
	trim_history(&env->histlist, hashlookup(env->localvar, "HISTSIZE"));
	ft_dlstadd(&env->histlist, ft_dlstnew("HEAD", 5));
}
