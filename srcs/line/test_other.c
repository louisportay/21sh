/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 18:34:08 by lportay           #+#    #+#             */
/*   Updated: 2018/03/14 12:39:05 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

bool	test_del_curr_char(t_ctx *ctx, t_line *l, t_key *key)
{
	if (!ft_strncmp(key->buf, DELETE, ft_strlen(DELETE)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (l->line->next)
			return (true);
		else
			return (false);
	}
	else if (*key->buf == C_D && ctx->emacs_mode && l->line->next)
		return (true);
	else
		return (false);
}

bool	test_del_prev_char(t_ctx *ctx, t_line *l, t_key *key)
{
	if (*key->buf == BACKSPACE && l->line->prev)
		return (true);
	else if (*key->buf == C_H && ctx->emacs_mode && l->line->prev)
		return (true);
	else
		return (false);
}

bool	test_emacs_mode(t_ctx *ctx, t_line *l, t_key *key)
{
	(void)ctx;
	(void)l;
	if (!ft_strncmp(key->buf, M_E, ft_strlen(M_E)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		return (true);
	}
	else
		return (false);
}

bool	test_clear_screen(t_ctx *ctx, t_line *l, t_key *key)
{
	(void)l;
	if (*key->buf == C_L && ctx->emacs_mode)
		return (true);
	else
		return (false);
}
