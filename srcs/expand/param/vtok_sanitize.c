/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtok_sanitize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 18:12:51 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/13 17:39:07 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

static t_vtok			*l_get_match(t_vtok *tok)
{
	t_vtok				*h;

	if (tok == NULL)
		return (NULL);
	h = tok;
	tok = tok->next;
	while ((tok = vtok_san_getnext(tok)) != NULL && tok->type != VACBRA)
		;
	if (tok == NULL)
		vtok_conv(h);
	return (tok == NULL ? NULL : tok->next);
}

static t_vtok			*l_get_dquote(t_vtok *tok)
{
	t_vtok				*next;

	tok = tok->next;
	vtok_split(tok, VDQUOT, &next);
	vtok_sanitize(tok);
	vtok_last(tok)->next = next;
	return (next->next);
}

static t_vtok			*l_get_vadoll(t_vtok *tok)
{
	if (vtok_isopen(tok))
		return (l_get_match(tok));
	else
		return (tok->next);
}

t_vtok					*vtok_san_getnext(t_vtok *tok)
{
	if (tok == NULL)
		return (NULL);
	else if (tok->type == VADOLL)
		return (l_get_vadoll(tok));
	else if (tok->type == VDQUOT)
		return (l_get_dquote(tok));
	else if (tok->type == VACBRA)
	{
		tok->type = VOTHER;
		tok->data.str = ft_strdup("}");
		return (tok->next);
	}
	else
		return (tok->next);
}

void					vtok_sanitize(t_vtok *tok)
{
	while ((tok = vtok_san_getnext(tok)) != NULL)
		;
}
