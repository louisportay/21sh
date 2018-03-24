/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtok_splitstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:56:29 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/24 14:36:57 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pattern_matching.h"

static void		l_handchar(char **str, t_qbuf *buf, t_list *lst[3])
{
	char		*tmp;

	if (**str == '/')
	{
		if (buf->used != 0)
		{
			tmp = qbuf_dump(buf);
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
		qbuf_addc(buf, **str);
		(*str)++;
	}
}

static t_list	*l_strsplitlist(char *str)
{
	t_list		*lst[3];
	t_qbuf		*buf;
	char		*tmp;

	lst[0] = NULL;
	buf = qbuf_new(1 << 8);
	while (*str != '\0')
		l_handchar(&str, buf, lst);
	if (buf->used != 0)
	{
		tmp = qbuf_dump(buf);
		lst[2] = list_create(tmp);
		ft_list_insert(lst, lst + 1, lst[2]);
	}
	ft_strdel(&buf->buffer);
	ft_memdel((void **)&buf);
	return (lst[0]);
}

static t_mtok	*mtok_split(t_mtok *t)
{
	t_list		*lst;
	t_list		*prev;
	t_mtok		*to[3];

	if ((lst = l_strsplitlist(t->data.str)) == NULL)
		return (NULL);
	to[0] = NULL;
	while (lst != NULL)
	{
		prev = lst;
		lst = lst->next;
		to[2] = mtok_create_str(STRIN, (char *)prev->content);
		mtok_insert(to, to + 1, to[2]);
		free(prev);
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
