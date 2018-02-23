/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_match.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 15:08:10 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/23 17:11:02 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_matching.h"
#include "dir_explorer.h"
#include "ft_21sh.h"

int					ent_match(char *str, t_mtok *tokens)
{
	if (get_ctxaddr(NULL)->set & DOTGLOB)
		return (compare(str,0, tokens) == 0);
	if (str[0] == '.' && tokens->type == FILEN)
		return (0);
	else
		return (compare(str, 0, tokens) == 0);
}
