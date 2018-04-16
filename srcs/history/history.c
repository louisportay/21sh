/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 13:39:52 by lportay           #+#    #+#             */
/*   Updated: 2018/04/10 09:38:00 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

t_histentry	*new_histentry(t_dlist *line, unsigned index)
{
	t_histentry *he;

	if (!(he = (t_histentry *)malloc(sizeof(t_histentry))))
		return (NULL);
	he->line = line;
	he->index = index;
	return (he);
}

void		del_histentry(void *histentry, size_t histentry_size)
{
	(void)histentry_size;
	ft_dlstdel(&T_HISTENTRY(histentry)->line, &delvoid);
	ft_memdel(&histentry);
}

void		insert_histlist(t_dlist *dup, t_hist *hist)
{
	t_histentry	*he;

	if ((he = new_histentry(dup, hist->index++)) == NULL)
	{
		ft_dlstdel(&dup, &delvoid);
		fatal_err(NOMEM, get_ctxaddr());
	}
	if ((dup = ft_dlstnewaddr(he, sizeof(t_histentry))) == NULL)
	{
		del_histentry(he, sizeof(t_histentry));
		fatal_err(NOMEM, get_ctxaddr());
	}
	ft_dlstinsert(hist->list, dup);
}

void		add_histentry(t_hist *hist, t_dlist *line)
{
	t_dlist		*dup;

	if ((dup = ft_dlstdup(line)) == NULL)
		fatal_err(NOMEM, get_ctxaddr());
	insert_histlist(dup, hist);
	trim_history(&hist->list->next, ft_astr_getval(get_ctxaddr()->locals,
													"HISTSIZE"));
}
