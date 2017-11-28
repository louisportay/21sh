/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 13:39:52 by lportay           #+#    #+#             */
/*   Updated: 2017/11/28 17:23:06 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int		get_histfile(t_21sh *env)
{
	char	*path;
	t_hash	*tmp;

	if (!(path = ft_getenv("HOME", env->environ)))
		env->histfile = open(".21sh_history", FLAGS, S_IWUSR | S_IRUSR);
	else
		env->histfile = open((path = fullpath(path, ".21sh_history")), FLAGS,
		S_IWUSR | S_IRUSR);
	if (env->histfile == -1)
		env->history = false;
	if (path)
	{
		if (!(tmp = hashcreate("HISTFILE", path, ft_strlen(path))))
			return (NOMEM);
		hashinsert(env->localvar, tmp, 0, &ft_memdel);
		ft_strdel(&path);
	}
	else if (env->history == true)
	{
		if (!(tmp = hashcreate("HISTFILE", ".21sh_history", 14)))
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
	ft_dlstdel(&T_HISTENTRY(histentry)->line, &delvoid);
	free(histentry);

}
void	del_history(t_dlist **histlist)
{
	t_dlist *tmp;

	tmp = *histlist;
	*histlist = (*histlist)->next;
	ft_dlstdelone(&tmp, &delvoid);
	ft_dlstdel(histlist, &del_histentry);
}

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
		str_to_dlst(histentry), env->histindex), sizeof(t_histentry *)));
			env->histindex++;
			free(histentry);
		}
	}
	ft_dlstadd(&env->histlist, ft_dlstnew("HEAD", 5));
}
