/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_match.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 15:08:10 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/07 17:06:06 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_matching.h"
#include "dir_explorer.h"

int					ent_match(char *str, t_mtok *tokens)
{
	if (str[0] == '.' && tokens->type == FILEN)
		return (0);
	else
		return (compare(str, 0, tokens) == 0);
}
