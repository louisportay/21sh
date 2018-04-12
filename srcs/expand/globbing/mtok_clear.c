/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtok_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 11:19:08 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/26 10:27:09 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pattern_matching.h"

void				mtok_clear(t_mtok **mt)
{
	t_mtok			*curr;
	t_mtok			*tmp;

	curr = *mt;
	*mt = NULL;
	while (curr != NULL)
	{
		tmp = curr;
		curr = curr->next;
		if (tmp->type == STRIN)
			ft_strdel(&tmp->data.str);
		ft_memdel((void **)&tmp);
	}
}
