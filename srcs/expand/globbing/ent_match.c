/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_match.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 15:08:10 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/20 14:34:51 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

int					ent_match(char *str, t_mtok *tokens)
{
	if (get_ctxaddr()->set & DOTGLOB)
		return (compare(str, 0, tokens) == 0);
	if (str[0] == '.' && tokens->type == FILEN)
		return (0);
	else
		return (compare(str, 0, tokens) == 0);
}
