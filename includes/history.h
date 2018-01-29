/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 12:04:48 by lportay           #+#    #+#             */
/*   Updated: 2018/01/27 17:24:57 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

#define HISTSIZE "20"
#define HISTFILESIZE "30"
#define HISTFILE ".21sh_history"

# define T_HISTENTRY(ptr)	((t_histentry *)ptr)

/* 
** histlist --> HEAD
**   			histentry --> line	--> HEAD
**				...					--> l
**									--> s
**									--> ' '
**									--> -
**									--> l
**									--> ...
**							--> index
**				dlist
** dlist		(histentry)
*/

typedef struct			s_hist
{
	t_dlist				*list;
	int					index;
	int					file;
}						t_hist;

typedef struct			s_histentry
{
	t_dlist		*line;
	unsigned	index;
}						t_histentry;

void		init_hist(t_21sh *env);
char		*get_histfile(t_21sh *env);
void		del_history(t_dlist	**history);
t_histentry	*new_histentry(t_dlist *line, unsigned index);
void		dump_history(t_dlist *histlist);
void		trim_history(t_dlist **histlist, char *histsize);
void		save_history(t_kvp *local, t_dlist *histlist);
void		del_histentry(void *histentry, size_t histentrysize);
void		add_histentry(t_21sh *env);

#endif
