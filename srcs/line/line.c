/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 17:38:36 by lportay           #+#    #+#             */
/*   Updated: 2018/02/07 18:30:05 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	init_line_funcs(t_line_pair *p)
{
	p[0] = TEST_FUNC(&test_upkey, &up_key);
	p[1] = TEST_FUNC(&test_downkey, &down_key);
	p[2] = TEST_FUNC(&test_lkey, &lkey);
	p[3] = TEST_FUNC(&test_rkey, &rkey);
	p[4] = TEST_FUNC(&test_del_current_char, &del_current_char);
	p[5] = TEST_FUNC(&test_del_previous_char, &del_previous_char);
	p[6] = TEST_FUNC(&test_line_beginning, &go_to_line_beginning);
	p[7] = TEST_FUNC(&test_line_end, &go_to_line_end);
	p[8] = TEST_FUNC(&test_lower_line, &go_lower_line);
	p[9] = TEST_FUNC(&test_upper_line, &go_upper_line);
	p[10] = TEST_FUNC(&test_go_prev_word, &go_to_previous_word);
	p[11] = TEST_FUNC(&test_go_next_word, &go_to_next_word);
	p[12] = TEST_FUNC(&test_kill_beginline, &kill_line_beginning);
	p[13] = TEST_FUNC(&test_kill_endline, &kill_line_end);
	p[14] = TEST_FUNC(&test_clear_screen, &clear_screen_);
	p[15] = TEST_FUNC(&test_yank, &yank);
	p[16] = TEST_FUNC(&test_emacs_mode, &reverse_emacs_mode);
	p[17] = TEST_FUNC(&test_killprevword, &kill_prev_word);
	//p[18] = LINE_FUNC(&test_killnextword, &kill_next_word);
	p[18] = TEST_FUNC(NULL, NULL);
}

int	read_state(t_ctx *ctx, t_line *l, t_key *key)
{
	if (*key->buf == NEWLINE_ || (ctx->emacs_mode && *key->buf == C_O))
	{
		if (l->line && ft_dlstaddr(l->line, 0) != l->lastline)
			ft_dlstdel(&l->lastline, &ft_memdel);
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

void	linefunc_switch(t_ctx *ctx, t_line *l, t_key *key)
{
	t_line_pair	p[19];
	int			i;

	i = 0;
	init_line_funcs(p);
	while (p[i].test && !(p[i].test(ctx, l, key)))
		i++;
	if (p[i].test)
		p[i].func(ctx, l);
}

int	user_input(t_ctx *ctx, t_line *l, t_key *key)
{
	int ret;

	if (test_load_line(ctx, l, key) == true)
		load_line(ctx, l);
	update_line(ctx, l);

	if ((ret = read_state(ctx, l, key)) != READON)
		return (ret);

	if (ft_isprint(*key->buf))
		insert_char(key->buf, ctx, l);
	else
		linefunc_switch(ctx, l, key);

	if ((key->buf[0] && key->buf[0] != ESC) || (key->buf[1] && key->buf[1] != '[') || key->i == READLEN)
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
	}
//	else if (buf == C_R && ctx->history)
//		recherche dans l'historique (C_G + C_J + C_O)
//	else if (buf == TAB && ctx->autocomplete)
//		autocompletion
	return (READON);
}

void	query_linestate(t_dlist *dlst, t_stack **linestate)
{
	if ((*linestate)->state == BSLASH)
		stack_pop(linestate);
	while (dlst && (*linestate)->state != HASH)
	{
		update_linestate(linestate, *(char *)(dlst->data));
		if (*(char *)(dlst->data) != '\\' && (*linestate)->state == BSLASH)
			stack_pop(linestate);
		dlst = dlst->next;
	}
	if ((*linestate)->state == HASH)
		stack_pop(linestate);
}

void	query_hdocstate(t_dlist *dlst, t_stack **linestate, char *eof)
{
	char *s;

	if (!(s = dlst_to_str(dlst)))
		return ;
	if (!ft_strcmp(s, eof))
		stack_pop(linestate);
	free(s);
}

void	join_split_lines(t_line *l)
{
	t_dlist *tmp;

	if (l->split_line && l->line->next)
	{
		tmp = l->split_line;
		ft_dlstend(&l->split_line);
		if (*(char *)l->split_line->data == '\\')
			ft_dlstremove(&l->split_line, &ft_memdel);
		l->line = l->line->next;
		ft_dlstdelone(&l->line->prev, &ft_memdel);
		l->line->prev = l->split_line;
		l->split_line->next = l->line;
		l->split_line = tmp;
	}
	else if (l->split_line && !l->line->next)
	{
		ft_dlstdelone(&l->line, &ft_memdel);
		tmp = l->split_line;
		ft_dlstend(&l->split_line);
		if (*(char *)l->split_line->data == '\\')
			ft_dlstremove(&l->split_line, &ft_memdel);
		l->split_line = tmp;
	}
	else if (!l->split_line)
		l->split_line = l->line;
}

void	err_quotes(t_line *l)
{
	write(STDIN_FILENO, "\n", 1);//
	dump_err(BADQUOTES);
	ft_dlstdel(&l->split_line, &ft_memdel);
	ft_dlstdel(&l->line, &ft_memdel);
	stack_del(&l->linestate);
}

void	wrap_lineread(t_ctx *ctx, t_line *l, char *prompt_mode)
{
	l->split_line = NULL;
	l->line_saved = false;
	ctx->cur_line = l;
	ft_strcpy(ctx->prompt_mode, prompt_mode);
	stack_push(&l->linestate, stack_create(UNQUOTED));

	if (ctx->line_edition)
	{
		lineread(ctx, &ctx->line);
		while (l->linestate && l->linestate->state != UNQUOTED)
			lineread(ctx, &ctx->line);
	}
	else
	{
		getrawline(ctx, &ctx->line);
		while (l->linestate && l->linestate->state != UNQUOTED)
			getrawline(ctx, &ctx->line);
	}
	ctx->cur_line = NULL;
	if (l->linestate)
		stack_del(&l->linestate);

	//DEBUG//
//	if (ctx->line.split_line)//
//		print_line(ctx->line.split_line->next);//print what's retrieved
//	write(1, "\n", 1);//
	/////////
}

