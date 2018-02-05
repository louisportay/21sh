/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 18:34:08 by lportay           #+#    #+#             */
/*   Updated: 2018/02/05 18:18:21 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_21sh.h"

bool	test_kill_beginline(t_21sh *env, t_line *l, t_key *key)
{
	(void)env;
	if (*key->buf == C_U && l->line->previous)
		return (true);
	else
		return (false);
}

bool	test_kill_endline(t_21sh *env, t_line *l, t_key *key)
{
	if (*key->buf == C_K && env->emacs_mode && l->line->next)
		return (true);
	else
		return (false);
}

bool	test_clear_screen(t_21sh *env, t_line *l, t_key *key)
{
	(void)l;
	if (*key->buf == C_L && env->emacs_mode) 
		return (true);
	else
		return (false);
}

bool	test_yank(t_21sh *env, t_line *l, t_key *key)
{
	if (*key->buf == C_Y && env->emacs_mode && l->yank)
		return (true);
	else
		return (false);
}

bool	test_go_next_word(t_21sh *env, t_line *l, t_key *key)
{
	if (!ft_strncmp(key->buf, M_F, ft_strlen(M_F)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (env->emacs_mode && l->line->next)
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

bool	test_go_prev_word(t_21sh *env, t_line *l, t_key *key)
{
	if (!ft_strncmp(key->buf, M_B, ft_strlen(M_B)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (env->emacs_mode && l->line->previous)
			return (true);
		else
			return (false);
	}
	else if (!ft_strncmp(key->buf, C_LEFT, ft_strlen(C_LEFT)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (l->line->previous)
			return (true);
		else
			return (false);
	}
	else
		return (false);
}

bool	test_upper_line(t_21sh *env, t_line *l, t_key *key)
{
	if (!ft_strncmp(key->buf, C_UP, ft_strlen(C_UP)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (l->cursor_offset >= env->ws.ws_col)
			return (true);
		else
			return (false);
	}
	else
		return (false);
}

bool	test_lower_line(t_21sh *env, t_line *l, t_key *key)
{
	(void)env;
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

bool	test_line_end(t_21sh *env, t_line *l, t_key *key)
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
	else if (*key->buf == C_E && env->emacs_mode && l->line->next)
		return (true);
	else
		return (false);
}

bool	test_line_beginning(t_21sh *env, t_line *l, t_key *key)
{
	if (!ft_strncmp(key->buf, HOME, ft_strlen(HOME)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (l->line->previous)
			return (true);
		else
			return (false);
	}
	else if (*key->buf == C_A && env->emacs_mode && l->line->previous)
		return (true);
	else
		return (false);
}

bool	test_upkey(t_21sh *env, t_line *l, t_key *key)
{
	(void)l;
	if (!ft_strncmp(key->buf, UP_KEY, ft_strlen(UP_KEY)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (env->history && env->hist.list->next)
			return (true);
		else
			return (false);
	}
	if (!env->history || !env->hist.list->next)
		return (false);
	else if (*key->buf == C_P && env->emacs_mode)
		return (true);
	else
		return (false);
}

bool	test_downkey(t_21sh *env, t_line *l, t_key *key)
{
	(void)l;
	if (!ft_strncmp(key->buf, DOWN_KEY, ft_strlen(DOWN_KEY)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (env->history && env->hist.list->previous)
			return (true);
		else
			return (false);
	}
	if (!env->history || !env->hist.list->previous)
		return (false);
	else if (*key->buf == C_N && env->emacs_mode)
		return (true);
	else
		return (false);
}

bool	test_rkey(t_21sh *env, t_line *l, t_key *key)
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
 	else if (*key->buf == C_F && env->emacs_mode && l->line->next)
		return (true);
	else
		return (false);
}

bool	test_lkey(t_21sh *env, t_line *l, t_key *key)
{
	if (!ft_strncmp(key->buf, LEFT_KEY, ft_strlen(LEFT_KEY)))
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
		if (l->line->previous)
			return (true);
		else
			return (false);
	}
	else if (*key->buf == C_B && env->emacs_mode && l->line->previous)
		return (true);
	else
		return (false);
}

bool	test_del_current_char(t_21sh *env, t_line *l, t_key *key)
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
	else if (*key->buf == C_D && env->emacs_mode && l->line->next)
		return (true);
	else
		return (false);
}

bool 	test_del_previous_char(t_21sh *env, t_line *l, t_key *key)
{
	if (*key->buf == BACKSPACE && l->line->previous)
		return (true);
	else if (*key->buf == C_H && env->emacs_mode && l->line->previous)
		return (true);
	else
		return (false);
}

bool	test_emacs_mode(t_21sh *env, t_line *l, t_key *key)
{
	(void)env;
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

/*
** Do not clear the buffer
*/

bool	test_load_line(t_21sh *env, t_line *l, t_key *key)
{
	if (l->line)
		return (false);
	else if (!ft_strncmp(key->buf, UP_KEY, ft_strlen(UP_KEY)))
		return (false);
	else if (!ft_strncmp(key->buf, DOWN_KEY, ft_strlen(DOWN_KEY)))
		return (false);
	else if (env->emacs_mode && (*key->buf == C_P || *key->buf == C_N))
		return (false);
	else
		return (true);
}

//bool	test_killnextword(t_21sh *env, t_line *l, t_key *key)
//{
//	if (!ft_strncmp(key->buf, M_D, ft_strlen(M_D)))
//	{
//		ft_bzero(key->buf, *bufindex);
//		key->i = 0;
//		if (l->line->next && env->emacs_mode)
//			return (true);
//		else
//			return (false);
//	}
//	else
//		return (false);
//
//}

bool	test_killprevword(t_21sh *env, t_line *l, t_key *key)
{
	(void)env;
	if (*key->buf == C_W && l->line->previous)
		return (true);
	else
		return (false);
}
