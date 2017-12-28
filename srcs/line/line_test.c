/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 18:34:08 by lportay           #+#    #+#             */
/*   Updated: 2017/12/22 16:03:50 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_21sh.h"

bool	test_kill_beginline(t_21sh *env, char *buf, int *bufindex)
{
	(void)bufindex;
	if (*buf == C_U && env->line->previous)
		return (true);
	else
		return (false);
}

bool	test_kill_endline(t_21sh *env, char *buf, int *bufindex)
{
	(void)bufindex;
	if (*buf == C_K && env->emacs_mode && env->line->next)
		return (true);
	else
		return (false);
}

bool	test_clear_screen(t_21sh *env, char *buf, int *bufindex)
{
	(void)bufindex;
	if (*buf == C_L && env->emacs_mode) 
		return (true);
	else
		return (false);
}

bool	test_yank(t_21sh *env, char *buf, int *bufindex)
{
	(void)bufindex;
	if (*buf == C_Y && env->emacs_mode && env->yank)
		return (true);
	else
		return (false);
}

bool	test_go_next_word(t_21sh *env, char *buf, int *bufindex)
{
	if (!ft_strncmp(buf, M_F, ft_strlen(M_F)))
	{
		ft_bzero(buf, *bufindex);
		*bufindex = 0;
		if (env->emacs_mode && env->line->next)
			return (true);
		else
			return (false);
	}
	else if (!ft_strncmp(buf, C_RIGHT, ft_strlen(C_RIGHT)))
	{
		ft_bzero(buf, *bufindex);
		*bufindex = 0;
		if (env->line->next)
			return (true);
		else
			return (false);
	}
	else
		return (false);
}

bool	test_go_prev_word(t_21sh *env, char *buf, int *bufindex)
{
	if (!ft_strncmp(buf, M_B, ft_strlen(M_B)))
	{
		ft_bzero(buf, *bufindex);
		*bufindex = 0;
		if (env->emacs_mode && env->line->previous)
			return (true);
		else
			return (false);
	}
	else if (!ft_strncmp(buf, C_LEFT, ft_strlen(C_LEFT)))
	{
		ft_bzero(buf, *bufindex);
		*bufindex = 0;
		if (env->line->previous)
			return (true);
		else
			return (false);
	}
	else
		return (false);
}

bool	test_upper_line(t_21sh *env, char *buf, int *bufindex)
{
	if (!ft_strncmp(buf, C_UP, ft_strlen(C_UP)))
	{
		ft_bzero(buf, *bufindex);
		*bufindex = 0;
		if (env->cursor_offset >= env->ws.ws_col)
			return (true);
		else
			return (false);
	}
	else
		return (false);
}

bool	test_lower_line(t_21sh *env, char *buf, int *bufindex)
{
	if (!ft_strncmp(buf, C_DOWN, ft_strlen(C_DOWN)))
	{
		ft_bzero(buf, *bufindex);
		*bufindex = 0;
		if (env->cursor_line < env->num_lines)
			return (true);
		else
			return (false);
	}
	else
		return (false);
}

bool	test_line_end(t_21sh *env, char *buf, int *bufindex)
{
	if (!ft_strncmp(buf, END, ft_strlen(END)))
	{
		ft_bzero(buf, *bufindex);
		*bufindex = 0;
		if (env->line->next)
			return (true);
		else
			return (false);
	}
	else if (*buf == C_E && env->emacs_mode && env->line->next)
		return (true);
	else
		return (false);
}

bool	test_line_beginning(t_21sh *env, char *buf, int *bufindex)
{
	if (!ft_strncmp(buf, HOME, ft_strlen(HOME)))
	{
		ft_bzero(buf, *bufindex);
		*bufindex = 0;
		if (env->line->previous)
			return (true);
		else
			return (false);
	}
	else if (*buf == C_A && env->emacs_mode && env->line->previous)
		return (true);
	else
		return (false);
}

bool	test_upkey(t_21sh *env, char *buf, int *bufindex)
{
	if (!ft_strncmp(buf, UP_KEY, ft_strlen(UP_KEY)))
	{
		ft_bzero(buf, *bufindex);
		*bufindex = 0;
		if (env->history && env->histlist->next)
			return (true);
		else
			return (false);
	}
	if (!env->history || !env->histlist->next)
		return (false);
	else if (*buf == C_P && env->emacs_mode)
		return (true);
	else
		return (false);
}

bool	test_downkey(t_21sh *env, char *buf, int *bufindex)
{
	if (!ft_strncmp(buf, DOWN_KEY, ft_strlen(DOWN_KEY)))
	{
		ft_bzero(buf, *bufindex);
		*bufindex = 0;
		if (env->history && env->histlist->previous)
			return (true);
		else
			return (false);
	}
	if (!env->history || !env->histlist->previous)
		return (false);
	else if (*buf == C_N && env->emacs_mode)
		return (true);
	else
		return (false);
}

bool	test_rkey(t_21sh *env, char *buf, int *bufindex)
{
	if (!ft_strncmp(buf, RIGHT_KEY, ft_strlen(RIGHT_KEY)))
	{
		ft_bzero(buf, *bufindex);
		*bufindex = 0;
		if (env->line->next)
			return (true);
		else
			return (false);
	}
 	else if (*buf == C_F && env->emacs_mode && env->line->next)
		return (true);
	else
		return (false);
}

bool	test_lkey(t_21sh *env, char *buf, int *bufindex)
{
	if (!ft_strncmp(buf, LEFT_KEY, ft_strlen(LEFT_KEY)))
	{
		ft_bzero(buf, *bufindex);
		*bufindex = 0;
		if (env->line->previous)
			return (true);
		else
			return (false);
	}
	else if (*buf == C_B && env->emacs_mode && env->line->previous)
		return (true);
	else
		return (false);
}

bool	test_del_current_char(t_21sh *env, char *buf, int *bufindex)
{
	if (!ft_strncmp(buf, DELETE, ft_strlen(DELETE)))
	{
		ft_bzero(buf, *bufindex);
		*bufindex = 0;
		if (env->line->next)
			return (true);
		else
			return (false);
	}
	else if (*buf == C_D && env->emacs_mode && env->line->next)
		return (true);
	else
		return (false);
}

bool 	test_del_previous_char(t_21sh *env, char *buf, int *bufindex)
{
	(void)bufindex;
	if (*buf == BACKSPACE && env->line->previous)
		return (true);
	else if ((*buf == C_H && env->emacs_mode) && env->line->previous)
		return (true);
	else
		return (false);
}

bool	test_emacs_mode(t_21sh *env, char *buf, int *bufindex)
{
	(void)env;
	if (!ft_strncmp(buf, M_E, ft_strlen(M_E)))
	{
		ft_bzero(buf, *bufindex);
		*bufindex = 0;
		return (true);
	}
	else
		return (false);

}

bool	test_load_line(t_21sh *env, char *buf)
{
	if (env->line)
		return (false);
	else if (!ft_strncmp(buf, UP_KEY, ft_strlen(UP_KEY)))
		return (false);
	else if (!ft_strncmp(buf, DOWN_KEY, ft_strlen(DOWN_KEY)))
		return (false);
	else if (env->emacs_mode && (*buf == C_P || *buf == C_N))
		return (false);
	else
		return (true);
}

//bool	test_killnextword(t_21sh *env, char *buf, int *bufindex)
//{
//	(void)bufindex;
//	if (!ft_strncmp(buf, M_D, ft_strlen(M_D)))
//	{
//		ft_bzero(buf, *bufindex);
//		*bufindex = 0;
//		if (env->line->next && env->emacs_mode)
//			return (true);
//		else
//			return (false);
//	}
//	else
//		return (false);
//
//}

bool	test_killprevword(t_21sh *env, char *buf, int *bufindex)
{
	(void)bufindex;
	if (*buf == C_W && env->line->previous)
		return (true);
	else
		return (false);
}
