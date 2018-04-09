/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtok_dollar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 10:53:29 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/08 19:34:34 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

static void			vtok_dollword(t_lvar *lvar)
{
	vtok_addvar(lvar->buf, lvar->ctx, lvar->curr_tok->next->data.str);
	lvar->curr_tok = lvar->curr_tok->next->next;
	lvar->next = &vtok_start;
}

static void			vtok_dollnull(t_lvar *lvar)
{
	vtok_tobuf(lvar->curr_tok, lvar->buf);
	lvar->exit_code = VAR_OK;
	lvar->next = NULL;
}

static void			vtok_dolldquote(t_lvar *lvar)
{
	lvar->curr_tok = lvar->curr_tok->next;
	lvar->next = &vtok_start;
}

void				vtok_vadoll(t_lvar *lvar)
{
	if (lvar->curr_tok->next == NULL)
		vtok_dollnull(lvar);
	else if (vtok_assert(lvar->curr_tok, 1, VADOLL))
		vtok_dolldoll(lvar);
	else if (vtok_assert(lvar->curr_tok, 1, VUNDER))
		vtok_dollunder(lvar);
	else if (vtok_assert(lvar->curr_tok, 1, VQUEST))
		vtok_dollquest(lvar);
	else if (vtok_assert(lvar->curr_tok, 1, VAWORD))
		vtok_dollword(lvar);
	else if (vtok_assert(lvar->curr_tok, 1, VDQUOT))
		vtok_dolldquote(lvar);
	else if (vtok_assert(lvar->curr_tok, 1, VAOBRA))
		vtok_dollvaobra(lvar);
	else
	{
		vtok_tobuf(lvar->curr_tok, lvar->buf);
		lvar->curr_tok = lvar->curr_tok->next;
		lvar->next = &vtok_start;
	}
}
