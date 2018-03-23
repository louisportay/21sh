/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_reset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 16:41:18 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/23 16:42:07 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				path_reset(t_ctx *ctx, int regen)
{
	hash_empty(ctx->hash, &ft_memdel);
	ft_astr_clear(&ctx->path);
	if (regen == 0)
		return ;
	if (ft_astr_getval(ctx->environ, "PATH") != NULL)
		ctx->path = getpath(ctx->environ);
	else if (ft_astr_getval(ctx->locals, "PATH") != NULL)
		ctx->path = getpath(ctx->locals);
}
