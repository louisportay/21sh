/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashinit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 15:39:20 by lportay           #+#    #+#             */
/*   Updated: 2017/11/16 17:31:51 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Init the whole hashtable depending on the HASHSIZE, every pointer to NULL
*/

void	hashinit(t_hash **table)
{
	int i;

	i = 0;
	while (i < HASHSIZE)
		table[i++] = NULL;
}
