/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 17:38:36 by lportay           #+#    #+#             */
/*   Updated: 2018/03/12 16:44:20 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	init_pairs(t_line_pair *p)
{
	p[0] = (t_line_pair){.test = &test_upkey, .func = &up_key};
	p[1] = (t_line_pair){.test = &test_downkey, .func = &down_key};
	p[2] = (t_line_pair){.test = &test_lkey, .func = &lkey};
	p[3] = (t_line_pair){.test = &test_rkey, .func = &rkey};
	p[4] = (t_line_pair){.test = &test_del_curr_char, .func = &del_curr_char};
	p[5] = (t_line_pair){.test = &test_del_prev_char, .func = &del_prev_char};
	
	p[6] = (t_line_pair){.test = &test_beginning,	.func = &go_beginning};
	p[7] = (t_line_pair){.test = &test_end, .func = &go_end};
	p[8] = (t_line_pair){.test = &test_lower_line, .func = &go_lower_line};
	p[9] = (t_line_pair){.test = &test_upper_line, .func = &go_upper_line};
	p[10] = (t_line_pair){.test = &test_prev_word, .func = &go_prev_word};
	p[11] = (t_line_pair){.test = &test_next_word, .func = &go_next_word};
	p[12] = (t_line_pair){.test = &test_kill_beginning, .func = &kill_beginning};
	p[13] = (t_line_pair){.test = &test_kill_end, .func = &kill_end};
	p[14] = (t_line_pair){.test = &test_kill_prev_word, .func = &kill_prev_word};
	p[15] = (t_line_pair){.test = &test_kill_next_word, .func = &kill_next_word};
	p[16] = (t_line_pair){.test = &test_yank, .func = &yank};
	p[17] = (t_line_pair){.test = &test_clear_screen, .func = &clear_screen_};
	p[18] = (t_line_pair){.test = &test_emacs_mode, 	.func = &toggle_emacs_mode};
	p[19] = (t_line_pair){.test = NULL, .func = NULL};
}

int	read_state(t_ctx *ctx, t_line *l, t_key *key)
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

void	line_switch(t_ctx *ctx, t_line *l, t_key *key)
{
	t_line_pair	p[20];
	int			i;

	i = 0;
	init_pairs(p);
	while (p[i].test && !(p[i].test(ctx, l, key)))
		i++;
	if (p[i].test)
		p[i].func(ctx, l);
}

/*
** When the line reader receives Ctrl-C
**
*/

void	reset_line(t_ctx *ctx, t_line *l)
{

	write(STDOUT_FILENO, "^C", 2);
	go_end(ctx, l);
	write(STDOUT_FILENO, "\n", 1);

	if (l->split_line)
		ft_dlstdel(&l->split_line, &delvoid);
	if (l->line)
		ft_dlsthead(&l->line);
	if (l->line && l->line != l->lastline)
	{
		ft_dlstdel(&l->line, &delvoid);
		ft_dlstdel(&l->lastline, &delvoid);
	}
	else
		ft_dlstdel(&l->lastline, &delvoid);

	stack_del(&l->linestate);	
	stack_push(&l->linestate, stack_create(UNQUOTED));
	ft_strcpy(ctx->prompt_mode, PS1);
	init_line(l);
}

void	reset_buffer(t_key *key)
{
	if ((key->buf[0] && key->buf[0] != ESC) ||
		(key->buf[1] && key->buf[1] != '[') ||
		key->i == READLEN)
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
	}
}
int	user_input(t_ctx *ctx, t_line *l, t_key *key)
{
	int ret;

	if ((ret = read_state(ctx, l, key)) != READON)
		return (ret);

	if (ft_isprint(*key->buf))
	{
		if (!l->num_lines)
			insert_char(key->buf, ctx, l);
		else
			insert_char_slow(key->buf, ctx, l);
	}
	else if (*key->buf == C_C)
		reset_line(ctx, l);
	else
		line_switch(ctx, l, key);

	reset_buffer(key);

//	else if (buf == C_R && ctx->history)
//		recherche dans l'historique (C_G + C_J + C_O)
//	else if (buf == TAB && ctx->autocomplete)
//		autocompletion

	return (READON);
}

void	join_split_lines(t_line *l)
{
	t_dlist *tmp;

	if (l->split_line && l->line->next)
	{
		tmp = l->split_line;
		ft_dlstend(&l->split_line);
		if (*(char *)l->split_line->data == '\\')
			ft_dlstremove(&l->split_line, &delvoid);
		l->line = l->line->next;
		ft_dlstdelone(&l->line->prev, &delvoid);
		l->line->prev = l->split_line;
		l->split_line->next = l->line;
		l->split_line = tmp;
	}
	else if (l->split_line && !l->line->next)
	{
		ft_dlstdelone(&l->line, &delvoid);
		tmp = l->split_line;
		ft_dlstend(&l->split_line);
		if (*(char *)l->split_line->data == '\\')
			ft_dlstremove(&l->split_line, &delvoid);
		l->split_line = tmp;
	}
	else if (!l->split_line)
		l->split_line = l->line;
}

void	err_line(t_line *l, int errno)
{
	write(STDIN_FILENO, "\n", 1);
	dump_err(errno);
	ft_dlstdel(&l->split_line, &delvoid);
	ft_dlstdel(&l->line, &delvoid);
//	stack_del(&l->linestate);
	stack_push(&l->linestate, stack_create(ERROR));
}

void	ft_readline(t_ctx *ctx, t_line *l, char *prompt_mode)
{
	l->split_line = NULL;
	ctx->cur_line = l;
	ft_strcpy(ctx->prompt_mode, prompt_mode);
	stack_push(&l->linestate, stack_create(UNQUOTED));
	if (l->heredoc)
		stack_push(&l->linestate, stack_create(HEREDOC));

	if (ctx->line_edition)
	{
		lineread(ctx, l);
		while (l->linestate->state != UNQUOTED && l->linestate->state != ERROR)
			lineread(ctx, l);
	}
	else
	{
		getrawline(ctx, l);
		while (l->linestate->state != UNQUOTED && l->linestate->state != ERROR)
			getrawline(ctx, l);
	}

	if (l->split_line)
	{
		add_histentry(&ctx->hist, l->split_line);
		ft_dlstaddend(l->split_line, ft_dlstnew("\n", 1));
	}

	ctx->cur_line = NULL;
	stack_del(&l->linestate);

	  //DEBUG//
   //  if (l->split_line)//
   //          print_line(l->split_line->next);//print what's retrieved
   //  write(1, "\n", 1);//
       /////////

}

