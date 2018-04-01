/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 13:07:48 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/01 13:09:33 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char					*list_flatten(t_list *list)
{
	t_qbuf				*buf;

	buf = qbuf_new(1 << 8);
	while (list != NULL)
	{
		qbuf_add(buf, (char *)list->content);
		if (list->next != NULL)
			qbuf_addc(buf, ' ');
		list = list->next;
	}
	return (qbuf_del(&buf));
}
