/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_go_to.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:56:04 by lportay           #+#    #+#             */
/*   Updated: 2018/03/14 13:56:06 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

bool	test_next_word(t_ctx *ctx, t_line *l, t_key *key)
{
	if (!ft_strncmp(key->buf, M_F, ft_strlen(M_F)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (ctx->emacs_mode && l->line->next)
			return (true);
		else
			return (false);
	}
	else if (!ft_strncmp(key->buf, C_RIGHT, ft_strlen(C_RIGHT)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (l->line->next)
			return (true);
		else
			return (false);
	}
	else
		return (false);
}

bool	test_prev_word(t_ctx *ctx, t_line *l, t_key *key)
{
	if (!ft_strncmp(key->buf, M_B, ft_strlen(M_B)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (ctx->emacs_mode && l->line->prev)
			return (true);
		else
			return (false);
	}
	else if (!ft_strncmp(key->buf, C_LEFT, ft_strlen(C_LEFT)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (l->line->prev)
			return (true);
		else
			return (false);
	}
	else
		return (false);
}

bool	test_end(t_ctx *ctx, t_line *l, t_key *key)
{
	if (!ft_strncmp(key->buf, END, ft_strlen(END)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (l->line->next)
			return (true);
		else
			return (false);
	}
	else if (*key->buf == C_E && ctx->emacs_mode && l->line->next)
		return (true);
	else
		return (false);
}

bool	test_beginning(t_ctx *ctx, t_line *l, t_key *key)
{
	if (!ft_strncmp(key->buf, HOME, ft_strlen(HOME)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (l->line->prev)
			return (true);
		else
			return (false);
	}
	else if (*key->buf == C_A && ctx->emacs_mode && l->line->prev)
		return (true);
	else
		return (false);
}
