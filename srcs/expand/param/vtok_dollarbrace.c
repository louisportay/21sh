/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtok_dollarbrace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 10:53:34 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/22 14:04:11 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

static void			vtok_dollbraceone(t_lvar *lvar)
{
	vtok_move(&lvar->curr_tok, 2);
	vtok_addvar(lvar->buf, lvar->ctx, lvar->curr_tok->data.str);
	vtok_move(&lvar->curr_tok, 2);
	lvar->next = &vtok_start;
}

static void			vtok_dolldflt(t_lvar *lvar)
{
	vtok_tobuf(lvar->curr_tok, lvar->buf);
	lvar->curr_tok = lvar->curr_tok->next;
	lvar->next = &vtok_start;
}

static void			vtok_getstr(t_lvar *lvar, t_vtok *tok, char **ret)
{
	t_vtok			*next;

	if (tok->next->type == VACBRA)
		*ret = ft_strdup("");
	else
	{
		vtok_splittilclose(tok->next, &next);
		vtok_handletokens(tok->next, ret, lvar->ctx);
		vtok_last(tok)->next = next;
	}
}

static void			vtok_dollvaobra_cond(t_lvar *lvar)
{
	t_vtok			*to[3];
	char			*str;
	char			*ret;
	char			*tmp;

	to[0] = vtok_peek(lvar->curr_tok, 2);
	if ((to[1] = vtok_peek_if(lvar->curr_tok, 3, VOTHER)) == NULL
		|| to[1]->data.str[0] != ':'
		|| ft_strindex("+-?", to[1]->data.str[1]) == -1)
	{
		lvar->next = &vtok_dolldflt;
		return ;
	}
	if ((str = to[1]->data.str)[2] != '\0')
	{
		tmp = ft_strdup(str + 2);
		to[2] = vtok_newstr(vtok_isword(tmp) ? VAWORD : VOTHER, tmp);
		to[2]->next = to[1]->next;
		to[1]->next = to[2];
	}
	vtok_getstr(lvar, to[1], &ret);
	vtok_dollexec(lvar, (char *[2]){to[0]->data.str, ret}, str[1]);
	ft_strdel(&ret);
	lvar->curr_tok = vtok_getclose(lvar->curr_tok->next);
	lvar->next = &vtok_start;
}

void				vtok_dollvaobra(t_lvar *lvar)
{
	if (vtok_assert(lvar->curr_tok, 2, VAWORD))
	{
		if (vtok_assert(lvar->curr_tok, 3, VACBRA))
			vtok_dollbraceone(lvar);
		else
			vtok_dollvaobra_cond(lvar);
	}
	else
		lvar->next = &vtok_dolldflt;
}
