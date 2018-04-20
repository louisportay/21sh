/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 17:37:57 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/20 15:55:18 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBBING_H
# define GLOBBING_H

# include "ft_42sh.h"

# include "pattern_matching.h"
# include "dir_explorer.h"

int				mtok_match(char *str, t_mtok *tok);
char			*glob_get_match(t_entry *ents, t_mtok *tok);
void			ent_insert_one(t_entry *tmps[2], t_entry *elem);

#endif
