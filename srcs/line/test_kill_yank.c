/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_kill_yank.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:56:18 by lportay           #+#    #+#             */
/*   Updated: 2018/03/21 11:12:43 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

bool	test_yank(t_ctx *ctx, t_line *l, t_key *key)
{
	(void)l;
	if (*key->buf == C_Y && ctx->emacs_mode && ctx->yank)
		return (true);
	else
		return (false);
}

bool	test_kill_beginning(t_ctx *ctx, t_line *l, t_key *key)
{
	(void)ctx;
	if (*key->buf == C_U && l->line->prev)
		return (true);
	else
		return (false);
}

bool	test_kill_end(t_ctx *ctx, t_line *l, t_key *key)
{
	if (*key->buf == C_K && ctx->emacs_mode && l->line->next)
		return (true);
	else
		return (false);
}

bool	test_kill_next_word(t_ctx *ctx, t_line *l, t_key *key)
{
	if (!ft_strncmp(key->buf, M_D, ft_strlen(M_D)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (l->line->next && ctx->emacs_mode)
			return (true);
		else
			return (false);
	}
	else
		return (false);
}

bool	test_kill_prev_word(t_ctx *ctx, t_line *l, t_key *key)
{
	(void)ctx;
	if (*key->buf == C_W && l->line->prev)
		return (true);
	else
		return (false);
}
