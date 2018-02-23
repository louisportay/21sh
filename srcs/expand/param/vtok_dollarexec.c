/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtok_dollarexec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:01:02 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/22 14:07:06 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

static void			vtok_plus(t_lvar *lvar, char *lhs, char *rhs)
{
	char			*elhs;

	elhs = ft_astr_getval(lvar->ctx->environ, lhs);
	if (elhs == NULL
		&& (elhs = ft_astr_getval(lvar->ctx->locals, lhs)) == NULL)
		return ;
	qbuf_add(lvar->buf, rhs);
}

static void			vtok_minus(t_lvar *lvar, char *lhs, char *rhs)
{
	char			*elhs;

	elhs = ft_astr_getval(lvar->ctx->environ, lhs);
	if (elhs == NULL
		&& (elhs = ft_astr_getval(lvar->ctx->locals, lhs)) == NULL)
		qbuf_add(lvar->buf, rhs);
	else
		qbuf_add(lvar->buf, elhs);
}

void				vtok_dollexec(t_lvar *lvar, char *str[2], char c)
{
	if (c == '+')
		vtok_plus(lvar, str[0], str[1]);
	else if (c == '-')
		vtok_minus(lvar, str[0], str[1]);
	else
		vtok_plus(lvar, str[0], str[1]);
}
