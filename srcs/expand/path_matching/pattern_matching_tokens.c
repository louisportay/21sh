/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_matching_tokens.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 12:43:29 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/05 13:10:16 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pattern_matching.h"

int				mtok_insert(t_mtok **head, t_mtok **curr, t_mtok *tmp)
{
	if (*head == NULL)
	{
		*head = tmp;
	}
	else
		(*curr)->next = tmp;
	*curr = mtok_last(tmp);
	return (1);
}

t_mtok			*mtok_create(enum e_mt_type type)
{
	t_mtok		*ret;

	if ((ret = (t_mtok *)ft_memalloc(sizeof(t_mtok))) == NULL)
		return (NULL);
	ret->type = type;
	ret->data.str = NULL;
	return (ret);
}

t_mtok			*mtok_create_mod(enum e_mt_type type, enum e_modtype mod)
{
	t_mtok		*ret;

	if ((ret = (t_mtok *)ft_memalloc(sizeof(t_mtok))) == NULL)
		return (NULL);
	ret->type = type;
	ret->data.mod = mod;
	return (ret);
}

t_mtok			*mtok_create_str(enum e_mt_type type, char *str)
{
	t_mtok		*ret;

	if ((ret = (t_mtok *)ft_memalloc(sizeof(t_mtok))) == NULL)
		return (NULL);
	ret->type = type;
	ret->data.str = str;
	return (ret);
}

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
