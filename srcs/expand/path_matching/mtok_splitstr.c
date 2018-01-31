/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtok_splitstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:56:29 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/07 14:25:40 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pattern_matching.h"

static void		l_handchar(char **str, t_membuf *buf, t_list *lst[3])
{
	char		*tmp;

	if (**str == '/')
	{
		if (ft_mb_getsize(buf) != 0)
		{
			tmp = ft_mb_fetch(buf);
			lst[2] = list_create(tmp);
			ft_list_insert(lst, lst + 1, lst[2]);
		}
		while (**str == '/')
			(*str)++;
		tmp = ft_strdup("/");
		lst[2] = list_create(tmp);
		ft_list_insert(lst, lst + 1, lst[2]);
	}
	else
	{
		ft_mb_addc(buf, **str);
		(*str)++;
	}
}

static t_list	*l_strsplitlist(char *str)
{
	t_list		*lst[3];
	t_membuf	buf;
	char		*tmp;

	lst[0] = NULL;
	ft_mb_init(&buf);
	while (*str != '\0')
		l_handchar(&str, &buf, lst);
	if (ft_mb_getsize(&buf) != 0)
	{
		tmp = ft_mb_fetch(&buf);
		lst[2] = list_create(tmp);
		ft_list_insert(lst, lst + 1, lst[2]);
	}
	return (lst[0]);
}

static t_mtok	*mtok_split(t_mtok *t)
{
	t_list		*lst;
	t_list		*head;
	t_mtok		*to[3];

	if ((lst = l_strsplitlist(t->data.str)) == NULL)
		return (NULL);
	head = lst;
	to[0] = NULL;
	while (lst != NULL)
	{
		to[2] = mtok_create_str(STRIN, (char *)lst->content);
		mtok_insert(to, to + 1, to[2]);
		lst = lst->next;
	}
	return (to[0]);
}

static t_mtok	*mtok_next(t_mtok *tmp)
{
	char		*str;

	if (tmp->type != STRIN && tmp->type != RANGE)
		return (mtok_create(tmp->type));
	else if ((tmp->type == STRIN && ft_strindex(tmp->data.str, '/') == -1)
				|| tmp->type == RANGE)
	{
		str = ft_strdup(tmp->data.str);
		return (mtok_create_str(tmp->type, str));
	}
	else
		return (mtok_split(tmp));
}

t_mtok			*mtok_splitstr(t_mtok *o)
{
	t_mtok		*head;
	t_mtok		*curr;
	t_mtok		*tmp;
	t_mtok		*created;

	head = NULL;
	curr = NULL;
	while (o != NULL)
	{
		tmp = o;
		o = o->next;
		if ((created = mtok_next(tmp)) == NULL)
		{
			mtok_clear(&head);
			return (NULL);
		}
		mtok_insert(&head, &curr, created);
	}
	return (head);
}
