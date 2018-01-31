/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttok_compose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 11:54:58 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/13 15:18:40 by vbastion         ###   ########.fr       */
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

static t_ttok		*l_tomix(t_btok **head)
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
			str = ft_strdup("");
		else
			str = substr(n, next);
		lst[2] = list_create(str);
		ft_list_insert(lst, lst + 1, lst[2]);
		if (next->type == BRCBRA)
			break ;
		n = next;
	}
	*head = next->next;
	return (ttok_newmix(lst[0]));
}

static t_ttok		*l_tosrange(t_btok **head)
{
	char			*str[2];
	int				*n;
	t_ttok			*ret;
	u_char			c;

	str[0] = btok_peek((*head), 1)->val;
	str[1] = btok_peek((*head), 4)->val;
	c = 0;
	if (ft_isnumber(str[0]) && ft_isnumber(str[1]))
	{
		n = (int[]){ ft_atoi(str[0]), ft_atoi(str[1])};
		c = 1;
	}
	else if (ft_islet(str[0]) && ft_islet(str[1]))
	{
		n = (int[]){ str[0][0], str[1][0] };
		c = 2;
	}
	else
		return (ttok_flatten(head));
	ret = ttok_newrng(c == 1 ? TNUMRNG : TALPRNG, n[0], n[1]);
	*head = btok_peek((*head), 6);
	return (ret);
}

t_ttok				*ttok_compose(t_btok **btok)
{
	t_btok			*n;

	n = (*btok)->next;
	if (btok_match(n, (int[]){BOTHER, BPOINT, BPOINT, BOTHER, BRCBRA, -1}))
		return (l_tosrange(btok));
	return (l_tomix(btok));
}
