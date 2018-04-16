/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtok_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 15:44:58 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/16 15:45:12 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

t_mtok			*mtok_last(t_mtok *last)
{
	if (last == NULL)
		return (NULL);
	if (last->next == NULL)
		return (last);
	while (last->next != NULL)
		last = last->next;
	return (last);
}
