/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_bridge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 17:35:16 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/10 18:18:22 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_dlist					*dlst_findc(t_dlist *elem, char c)
{
	while (elem != NULL)
	{
		if (*((char *)elem->data) == c)
			return (elem);
		elem = elem->next;
	}
	return (NULL);
}

size_t					dlst_pcount(t_dlist *beg, t_dlist *end)
{
	size_t				len;

	len = 0;
	while (beg != NULL && beg != end)
	{
		beg = beg->next;
		len++;
	}
	return (len);
}

char					*dlst_pstr(t_dlist *beg, t_dlist *end)
{
	size_t				len;
	char				*ret;
	int					i;

	len = dlst_pcount(beg, end);
	ret = ft_strnew(len);
	i = 0;
	while (beg != NULL && beg != end)
	{
		ret[i] = *((char *)beg->data);
		beg = beg->next;
		i++;
	}
	return (ret);
}
