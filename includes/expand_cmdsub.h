/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmdsub.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 17:13:43 by lportay           #+#    #+#             */
/*   Updated: 2018/04/19 16:35:07 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_CMDSUB_H
# define EXPAND_CMDSUB_H

#include "ft_42sh.h"

int		expand_cmdsub(char *s, char **new_s);

int		bquotes_exp(char *s, char *opening_bquote, char **new_s);
int		match_bquotes(char *s, char **o_bquote);

void	subshell(int fd[2], t_dlist *cmd);
void	read_from_subshell(int fd[2], char *c_bquote, t_qbuf *qbuf);

#endif
