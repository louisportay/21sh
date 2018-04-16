/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_bridge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 17:35:16 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/21 10:20:32 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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
	if ((ret = ft_strnew(len)) == NULL)
		return (NULL);
	i = 0;
	while (beg != NULL && beg != end)
	{
		ret[i] = *((char *)beg->data);
		beg = beg->next;
		i++;
	}
	return (ret);
}
