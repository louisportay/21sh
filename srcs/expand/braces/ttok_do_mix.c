/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttok_do_mix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 19:05:54 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/11 19:19:21 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_braces.h"

static t_btok		*get_next(t_btok *tok)
{
	int				depth;

	depth = 0;
	while (1)
	{
		if (tok->next->type == BROBRA)
			depth++;
		else if (tok->next->type == BCOMMA && depth == 0)
			return (tok->next);
		else if (tok->next->type == BRCBRA)
		{
			if (depth == 0)
				return (tok->next);
			else
				depth--;
		}
		tok = tok->next;
	}
}

static char			*substr(t_btok *n, t_btok *next)
{
	t_btok			*t_head;
	t_btok			*t_tail;
	t_ttok			*subchain;
	char			*str;

	t_tail = ttok_before(next, n);
	t_tail->next = NULL;
	t_head = n->next;
	subchain = ttok_get(t_head);
	str = ttok_combine(subchain);
	ttok_clear(&subchain);
	t_tail->next = next;
	return (str);
}

static t_list		*splitstr_tolist(char *str)
{
	char			**astr;
	size_t			i;
	t_list			*lst[3];

	lst[0] = NULL;
	astr = ft_strsplit(str, ' ');
	i = 0;
	while (astr[i] != NULL)
	{
		if ((lst[2] = list_create(astr[i])) == NULL)
			fatal_err(NOMEM, get_ctxaddr());
		ft_list_insert(lst, lst + 1, lst[2]);
		i++;
	}
	free(astr);
	return (lst[0]);
}

static void			do_subchain(t_btok *n, t_btok *next, t_list *lst[3])
{
	char			*str;

	if ((str = substr(n, next)) == NULL)
		fatal_err(NOMEM, get_ctxaddr());
	if ((lst[2] = splitstr_tolist(str)) == NULL)
		fatal_err(NOMEM, get_ctxaddr());
	ft_strdel(&str);
	if (lst[0] == NULL)
		lst[0] = lst[2];
	else
		lst[1]->next = lst[2];
	lst[1] = ft_list_last(lst[2]);
}

t_ttok				*ttok_do_mix(t_btok **head)
{
	t_btok			*n;
	t_btok			*next;
	char			*str;
	t_list			*lst[3];

	n = *head;
	lst[0] = NULL;
	while ((next = get_next(n)))
	{
		if (next == n->next)
		{
			if ((str = ft_strdup("")) == NULL)
				fatal_err(NOMEM, get_ctxaddr());
			if ((lst[2] = list_create(str)) == NULL)
				fatal_err(NOMEM, get_ctxaddr());
			ft_list_insert(lst, lst + 1, lst[2]);
		}
		else
			do_subchain(n, next, lst);
		if (next->type == BRCBRA)
			break ;
		n = next;
	}
	*head = next->next;
	return (ttok_newmix(lst[0]));
}
