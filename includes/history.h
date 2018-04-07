/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 12:04:48 by lportay           #+#    #+#             */
/*   Updated: 2018/04/07 09:39:49 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# define HISTSIZE		"100"
# define HISTFILESIZE	"100"
# define HISTFILE		".21sh_history"

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

typedef struct s_ctx	t_ctx;

typedef struct			s_hist
{
	t_dlist				*list;
	unsigned			index;
	unsigned			first_entry;
}						t_hist;

typedef struct			s_histentry
{
	t_dlist				*line;
	unsigned			index;
}						t_histentry;

void					init_hist(t_hist *hist, char *histfile);
void					add_histfile(t_ctx *env);
void					del_histentry(void *histentry, size_t histentry_size);
void					del_history(t_dlist **history);
t_histentry				*new_histentry(t_dlist *line, unsigned index);
void					trim_history(t_dlist **histlist, char *histsize);
void					save_history(char *histfile, t_dlist *histlist,
		int flags);
void					add_histentry(t_hist *hist, t_dlist *line);
char					*dump_history(t_dlist *histlist, int n);

void					history_expansion(t_hist *hist, t_dlist *dlst);

#endif
