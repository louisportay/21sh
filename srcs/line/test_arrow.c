/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_arrow.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:55:46 by lportay           #+#    #+#             */
/*   Updated: 2018/03/14 13:55:47 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

bool	test_rkey(t_ctx *ctx, t_line *l, t_key *key)
{
	if (!ft_strncmp(key->buf, RIGHT_KEY, ft_strlen(RIGHT_KEY)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (l->line->next)
			return (true);
		else
			return (false);
	}
	else if (*key->buf == C_F && ctx->emacs_mode && l->line->next)
		return (true);
	else
		return (false);
}

bool	test_lkey(t_ctx *ctx, t_line *l, t_key *key)
{
	if (!ft_strncmp(key->buf, LEFT_KEY, ft_strlen(LEFT_KEY)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (l->line->prev)
			return (true);
		else
			return (false);
	}
	else if (*key->buf == C_B && ctx->emacs_mode && l->line->prev)
		return (true);
	else
		return (false);
}

bool	test_upkey(t_ctx *ctx, t_line *l, t_key *key)
{
	(void)l;
	if (!ft_strncmp(key->buf, UP_KEY, ft_strlen(UP_KEY)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (ctx->hist.list->next)
			return (true);
		else
			return (false);
	}
	if (*key->buf == C_P && ctx->emacs_mode && ctx->hist.list->next)
		return (true);
	else
		return (false);
}

bool	test_downkey(t_ctx *ctx, t_line *l, t_key *key)
{
	(void)l;
	if (!ft_strncmp(key->buf, DOWN_KEY, ft_strlen(DOWN_KEY)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (ctx->hist.list->prev)
			return (true);
		else
			return (false);
	}
	if (*key->buf == C_N && ctx->emacs_mode && ctx->hist.list->prev)
		return (true);
	else
		return (false);
}
