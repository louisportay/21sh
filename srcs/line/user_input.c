/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 11:51:16 by lportay           #+#    #+#             */
/*   Updated: 2018/04/16 18:06:13 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static t_line_pair	*init_pairs(void)
{
	static t_line_pair	p[21];

	p[0] = (t_line_pair){.test = &test_upkey, .fun = &up_key};
	p[1] = (t_line_pair){.test = &test_downkey, .fun = &down_key};
	p[2] = (t_line_pair){.test = &test_lkey, .fun = &lkey};
	p[3] = (t_line_pair){.test = &test_rkey, .fun = &rkey};
	p[4] = (t_line_pair){.test = &test_del_curr_char, .fun = &del_curr_char};
	p[5] = (t_line_pair){.test = &test_del_prev_char, .fun = &del_prev_char};
	p[6] = (t_line_pair){.test = &test_beginning, .fun = &go_beginning};
	p[7] = (t_line_pair){.test = &test_end, .fun = &go_end};
	p[8] = (t_line_pair){.test = &test_lower_line, .fun = &go_lower_line};
	p[9] = (t_line_pair){.test = &test_upper_line, .fun = &go_upper_line};
	p[10] = (t_line_pair){.test = &test_prev_word, .fun = &go_prev_word};
	p[11] = (t_line_pair){.test = &test_next_word, .fun = &go_next_word};
	p[12] = (t_line_pair){.test = &test_kill_beginning, .fun = &kill_beginning};
	p[13] = (t_line_pair){.test = &test_kill_end, .fun = &kill_end};
	p[14] = (t_line_pair){.test = &test_kill_prev_word, .fun = &kill_prev_word};
	p[15] = (t_line_pair){.test = &test_kill_next_word, .fun = &kill_next_word};
	p[16] = (t_line_pair){.test = &test_yank, .fun = &yank};
	p[17] = (t_line_pair){.test = &test_clear_screen, .fun = &clear_screen_};
	p[18] = (t_line_pair){.test = &test_emacs_mode, .fun = &toggle_emacs_mode};
	p[19] = (t_line_pair){.test = &test_autocomplete, .fun = &autocomplete};
	p[20] = (t_line_pair){.test = NULL, .fun = NULL};
	return (p);
}

static int	read_state(t_ctx *ctx, t_line *l, t_key *key)
{
	if (*key->buf == NL || (ctx->emacs_mode && *key->buf == C_O))
	{
		if (l->line && ft_dlstaddr(l->line, 0) != l->lastline)
			ft_dlstdel(&l->lastline, &delvoid);
		return (FINISHREAD);
	}
	else if (*key->buf == C_D && !ft_dlstcount(l->line))
	{
		if (l->linestate->state == UNQUOTED)
			return (EXITSHELL);
		else
			return (ERR_QUOTE);
	}
	return (READON);
}

static void	line_switch(t_ctx *ctx, t_line *l, t_key *key)
{
	static t_line_pair *p = NULL;
	int					i;

	i = 0;
	if (!p)
		p = init_pairs();
	while (p[i].test && !(p[i].test(ctx, l, key)))
		i++;
	if (p[i].test)
		p[i].fun(ctx, l);
}

static void	reset_buffer(t_key *key)
{
	if ((key->buf[0] && key->buf[0] != ESC) ||
		(key->buf[1] && key->buf[1] != '[') ||
		key->i == READLEN)
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
	}
}

/*
** C_R --> recherche dans l'historique (C_G + C_J + C_O)
** C_I --> autocompletion
*/

int			user_input(t_ctx *ctx, t_line *l, t_key *key)
{
	int ret;

	if ((ret = read_state(ctx, l, key)) != READON)
		return (ret);
	if (ft_isprint(*key->buf))
		insert_char(key->buf, ctx, l);
	else
		line_switch(ctx, l, key);
	reset_buffer(key);
	return (READON);
}
