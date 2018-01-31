/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtok_handletokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 18:09:23 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/10 15:57:36 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

void				vtok_start(t_lvar *lvar)
{
	if (lvar->curr_tok == NULL)
	{
		lvar->exit_code = VAR_OK;
		lvar->next = NULL;
	}
	else if (lvar->curr_tok->type == VADOLL)
		lvar->next = &vtok_vadoll;
	else
	{
		vtok_tobuf(lvar->curr_tok, &lvar->buf);
		lvar->curr_tok = lvar->curr_tok->next;
		lvar->next = &vtok_start;
	}
}

int					vtok_handletokens(t_vtok *tokens, char **ret,
										t_environ *env)
{
	t_lvar			lvar;

	if (tokens == NULL)
		return (1);
	ft_mb_init(&lvar.buf);
	lvar.tokens = tokens;
	lvar.curr_tok = tokens;
	lvar.next = &vtok_start;
	lvar.env = env;
	while (lvar.next != NULL)
		lvar.next(&lvar);
	if (lvar.exit_code == VAR_OK)
		*ret = ft_mb_fetch(&lvar.buf);
	else if (lvar.exit_code == VAR_ERR)
		*ret = lvar.exit_message;
	return (lvar.exit_code);
}
