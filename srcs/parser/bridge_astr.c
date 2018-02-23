/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge_astr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 19:59:53 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/21 19:34:32 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char					**astr_fromlist(t_list **lst)
{
	t_list				*curr;
	t_list				*tmp;
	char				**arr;
	size_t				len;
	int					i;

	curr = *lst;
	len = ft_list_len(curr) + 1;
	arr = (char **)ft_pmemalloc(sizeof(char *) * len, &on_emem, NOMEM);
	i = 0;
	while (curr != NULL)
	{
		tmp = curr;
		curr = curr->next;
		arr[i] = (char *)tmp->content;
		ft_memdel((void **)&tmp);
		i++;
	}
	return (arr);
}
