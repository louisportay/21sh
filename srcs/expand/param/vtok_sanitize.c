/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtok_sanitize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 18:12:51 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/11 14:26:19 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

static t_vtok		*do_subexpr(t_vtok *tok, int depth, int *err)
{
	t_vtok			*next;
	t_vtok			*last;

	next = NULL;
	tok = tok->next;
	vtok_split(tok, VDQUOT, &next);
	if ((vtok_sanitize(tok, depth + 1, err)))
		return (NULL);
	if (tok == NULL)
		return (NULL);
	last = vtok_last(tok);
	if (last != NULL)
	{
		last->next = next;
		return (next);
	}
	return (next);
}

static t_vtok		*get_match(t_vtok *tok, int depth, int *err)
{
	t_vtok			*h;

	h = tok;
	if (tok->next == NULL)
		return (NULL);
	tok = tok->next;
	while (tok != NULL && tok->type != VACBRA)
		tok = vtok_get_next(tok, depth, err);
	if (*err)
		return (NULL);
	if (tok == NULL)
		vtok_conv(h);
	return (tok != NULL ? tok->next : NULL);
}

t_vtok				*vtok_get_next(t_vtok *tok, int depth, int *err)
{
	if (tok->type == VADOLL)
	{
		if (vtok_isopen(tok))
			return (get_match(tok, depth, err));
		else
			return (tok->next);
	}
	else if (tok->type == VDQUOT)
		return (do_subexpr(tok, depth, err));
	else if (tok->type == VACBRA)
	{
		tok->type = VOTHER;
		tok->data.str = ft_strdup("}");
	}
	return (tok->next);
}

int					vtok_sanitize(t_vtok *tok, int depth, int *err)
{
	if (depth > PARAM_DEPTH)
	{
		*err = 1;
		return (1);
	}
	depth += 1;
	while (tok != NULL)
		tok = vtok_get_next(tok, depth, err);
	return (*err ? 1 : 0);
}
