/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtok_dollunder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 12:50:58 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/12 12:53:07 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

static void			vtok_dodollunder(t_lvar *lvar)
{
	t_ctx			*ctx;

	ctx = get_ctxaddr();
	if (ctx->last_argv != NULL)
		qbuf_add(lvar->buf, ctx->last_argv);
	lvar->curr_tok = lvar->curr_tok->next->next;
	lvar->next = &vtok_start;
}

static void			vtok_convunder(t_lvar *lvar)
{
	t_vtok			*tmp;
	t_vtok			*rep;
	t_vtok			*next;
	t_qbuf			*buf;

	tmp = lvar->curr_tok->next;
	while (tmp->next != NULL && (tmp->next->type == VUNDER
									|| tmp->next->type == VAWORD))
		tmp = tmp->next;
	next = tmp->next;
	tmp->next = NULL;
	buf = qbuf_new(1 << 8);
	tmp = lvar->curr_tok->next;
	while (tmp != NULL)
	{
		if (tmp->type == VUNDER)
			qbuf_addc(buf, '_');
		else
			qbuf_add(buf, tmp->data.str);
		tmp = tmp->next;
	}
	rep = vtok_newstr(VAWORD, qbuf_del(&buf));
	vtok_clear(&lvar->curr_tok->next);
	lvar->curr_tok->next = rep;
	lvar->curr_tok->next->next = next;
}

void				vtok_dollunder(t_lvar *lvar)
{
	if (lvar->curr_tok->next->next == NULL
		|| (vtok_assert(lvar->curr_tok, 2, VUNDER) == 0
			&& vtok_assert(lvar->curr_tok, 2, VAWORD) == 0))
		vtok_dodollunder(lvar);
	else
	{
		vtok_convunder(lvar);
		vtok_dollword(lvar);
	}
}
