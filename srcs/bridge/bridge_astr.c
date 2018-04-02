/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bridge_astr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 13:12:46 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/02 14:21:35 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void					astr_to_buf(char **argv, t_qbuf *buf, int last)
{
	int					i;

	i = 0;
	while (argv[i] != NULL)
	{
		qbuf_add(buf, argv[i]);
		if (argv[i + 1] != NULL)
			qbuf_addc(buf, ' ');
		else
			qbuf_add(buf, last ? "" : " | ");
		i++;
	}
}

void					astr_env_replace(char ***env, char *key, char *new_v)
{
	int					i;
	char				**e;
	char				*str;

	e = *env;
	str = ft_strjoinc(key, new_v, '=');
	if ((i = ft_astr_getkey(e, key, ft_strlen(key))) == -1)
		ft_astr_append(&e, str);
	else
	{
		ft_strdel(e + i);
		e[i] = str;
	}
	*env = e;
}

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
	*lst = NULL;
	return (arr);
}
