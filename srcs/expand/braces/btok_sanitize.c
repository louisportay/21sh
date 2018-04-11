/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btok_sanitize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 18:08:23 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/11 11:35:57 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_braces.h"

t_btok					*l_get_match(t_btok *tok)
{
	t_btok				*h;

	if (tok == NULL)
		return (NULL);
	h = tok;
	tok = tok->next;
	while ((tok = btok_san_getnext(tok)) != NULL && tok->type != BRCBRA)
		;
	if (tok == NULL)
		h->type = BOTHER;
	return (tok == NULL ? NULL : tok->next);
}

t_btok					*l_handle_dollar(t_btok *tok)
{
	tok->type = BOTHER;
	tok = tok->next;
	if (tok == NULL)
		return (NULL);
	if (tok->type == BROBRA)
	{
		tok->type = BOTHER;
		while ((tok = btok_san_getnext(tok)) != NULL && tok->type != BRCBRA)
			;
		if (tok != NULL)
			tok->type = BOTHER;
		return (tok == NULL ? NULL : tok->next);
	}
	return (tok);
}

t_btok					*btok_san_getnext(t_btok *tok)
{
	if (tok == NULL)
		return (NULL);
	else if (tok->type == BRDOLL)
		return (l_handle_dollar(tok));
	else if (tok->type == BROBRA)
		return (l_get_match(tok));
	else if (tok->type == BRCBRA)
		tok->type = BOTHER;
	return (tok->next);
}

int						btok_sanitize(t_btok *tok)
{
	while ((tok = btok_san_getnext(tok)) != NULL)
		;
	return (1);
}
