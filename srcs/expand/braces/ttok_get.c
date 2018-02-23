/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttok_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 19:01:55 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/23 19:40:27 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_braces.h"

//added (unsigned)

int					btok_match(t_btok *head, int *es)
{
	if (es == NULL)
		return (0);
	while (head != NULL && *es != -1)
	{
		if (head->type != (unsigned)*es)
			return (0);
		head = head->next;
		es++;
	}
	return (*es == -1);
}

t_ttok				*l_redo_until(t_btok **btok, enum e_btoktype type)
{
	t_qbuf			*buf;
	t_btok			*t;

	t = *btok;
	buf = qbuf_new(1 << 8);
	while (t->type == type)
	{
		qbuf_add(buf, t->val);
		t = t->next;
	}
	*btok = t;
	return (ttok_newstr(qbuf_del(&buf)));
}

t_ttok				*l_redo_past(t_btok **btok, enum e_btoktype type)
{
	t_qbuf			*buf;
	t_btok			*t;

	t = *btok;
	buf = qbuf_new(1 << 8);
	while (1)
	{
		qbuf_add(buf, t->val);
		t = t->next;
		if (t->type == type)
			break ;
	}
	*btok = t;
	return (ttok_newstr(qbuf_del(&buf)));
}

t_ttok				*ttok_next(t_btok **btok)
{
	t_ttok			*t;

	if (*btok == NULL)
		return (NULL);
	if ((*btok)->type == BROBRA)
		return (ttok_compose(btok));
	t = ttok_newstr(ft_strdup((*btok)->val));
	*btok = (*btok)->next;
	return (t);
}

t_ttok				*ttok_get(t_btok *btok)
{
	t_ttok			*tok[3];

	tok[0] = NULL;
	while ((tok[2] = ttok_next(&btok)) != NULL)
		ttok_insert(tok, tok + 1, tok[2]);
	return (tok[0]);
}
