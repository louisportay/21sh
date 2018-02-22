/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttok_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 15:19:41 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/22 11:56:04 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_braces.h"

t_btok				*ttok_before(t_btok *next, t_btok *from)
{
	if (next == NULL)
		return (NULL);
	while (from->next != next)
		from = from->next;
	return (from);
}

int					ft_islet(char *str)
{
	return (str[0] != '\0' && ft_isalpha(str[0]) && str[1] == '\0');
}

int					btok_assert(t_btok *tok, int n, enum e_btoktype type)
{
	if (tok == NULL)
		return (0);
	while (n > 0)
	{
		if (tok == NULL)
			return (0);
		tok = tok->next;
		n--;
	}
	return (tok != NULL && tok->type == type);
}

t_btok				*btok_peek(t_btok *tok, int n)
{
	while (n > 0)
	{
		if (tok == NULL)
			return (NULL);
		n--;
		tok = tok->next;
	}
	return (tok);
}

t_ttok				*ttok_flatten(t_btok **head)
{
	t_ttok			*ret;
	t_qbuf			*buf;
	char			*str;
	t_btok			*curr;

	curr = *head;
	buf = qbuf_new(1 << 8);
	while (1)
	{
		str = curr->val;
		qbuf_add(buf, str);
		if (curr->type == BRCBRA)
			break ;
		curr = curr->next;
	}
	ret = ttok_newstr(qbuf_del(&buf));
	*head = curr->next;
	return (ret);
}
