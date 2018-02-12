/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge_astr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 19:59:53 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/10 20:06:57 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char				**astr_fromlist(t_list *list)
{
	char			**ret;
	size_t			len;
	size_t			i;

	len = ft_list_len(list);
	ret = (char **)ft_pmemalloc(sizeof(t_list *) * (len + 1), &on_emem, NOMEM);
	i = 0;
	while (i < len)
	{
		ret[i] = (char *)list->content;
		i++;
		list = list->next;
	}
	return (ret);
}
