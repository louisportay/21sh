/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 18:34:08 by lportay           #+#    #+#             */
/*   Updated: 2018/03/11 16:39:55 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_21sh.h"

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

bool	test_clear_screen(t_ctx *ctx, t_line *l, t_key *key)
{
	(void)l;
	if (*key->buf == C_L && ctx->emacs_mode) 
		return (true);
	else
		return (false);
}

bool	test_yank(t_ctx *ctx, t_line *l, t_key *key)
{
	if (*key->buf == C_Y && ctx->emacs_mode && l->yank)
		return (true);
	else
		return (false);
}

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

bool	test_upper_line(t_ctx *ctx, t_line *l, t_key *key)
{
	(void)ctx;
	if (!ft_strncmp(key->buf, C_UP, ft_strlen(C_UP)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (l->cursor_line != 0)
			return (true);
		else
			return (false);
	}
	else
		return (false);
}

bool	test_lower_line(t_ctx *ctx, t_line *l, t_key *key)
{
	(void)ctx;
	if (!ft_strncmp(key->buf, C_DOWN, ft_strlen(C_DOWN)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (l->cursor_line < l->num_lines)
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

bool 	test_del_prev_char(t_ctx *ctx, t_line *l, t_key *key)
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
