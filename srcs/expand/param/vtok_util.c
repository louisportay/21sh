/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtok_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 18:12:07 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/22 13:59:27 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

void			vtok_tobuf(t_vtok *tok, t_qbuf *buf)
{
	if (tok->type == VAWORD || tok->type == VOTHER)
		qbuf_add(buf, tok->data.str);
	else
		qbuf_addc(buf, tok->data.c);
}

int				vtok_assert(t_vtok *tok, int n, enum e_vtype type)
{
	while (n > 0)
	{
		if (tok == NULL)
			return (0);
		tok = tok->next;
		n--;
	}
	return (tok == NULL ? 0 : tok->type == type);
}

int				vtok_move(t_vtok **tok, int n)
{
	t_vtok		*t;

	t = *tok;
	while (n > 0)
	{
		if (t == NULL)
			return (0);
		t = t->next;
		n--;
	}
	*tok = t;
	return (1);
}

t_vtok			*vtok_peek(t_vtok *tok, int n)
{
	if (tok == NULL)
		return (NULL);
	while (n > 0)
	{
		if (tok == NULL)
			return (NULL);
		tok = tok->next;
		n--;
	}
	return (tok);
}

t_vtok			*vtok_peek_if(t_vtok *tok, int n, enum e_vtype type)
{
	if (tok == NULL)
		return (NULL);
	while (n > 0)
	{
		if (tok == NULL)
			return (NULL);
		tok = tok->next;
		n--;
	}
	return ((tok != NULL && tok->type == type) ? tok : NULL);
}
