/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 13:39:52 by lportay           #+#    #+#             */
/*   Updated: 2018/03/19 18:44:19 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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

void		add_histentry(t_hist *hist, t_dlist *line)
{
	ft_dlstinsert(hist->list, ft_dlstnewaddr(new_histentry(ft_dlstdup(line),
					hist->index++), sizeof(t_histentry)));
	trim_history(&hist->list->next, ft_astr_getval(get_ctxaddr()->locals,
				"HISTSIZE"));
}
