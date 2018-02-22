/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vtok_addvar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 11:52:54 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/22 14:02:51 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

void				vtok_addvar(t_qbuf *buf, t_ctx *ctx, char *key)
{
	char			*value;

	value = ft_astr_getval(ctx->environ, key);
	if (value == NULL && (value = ft_astr_getval(ctx->locals, key)) == NULL)
		return ;
	qbuf_add(buf, value);
}
