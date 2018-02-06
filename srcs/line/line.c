/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 17:38:36 by lportay           #+#    #+#             */
/*   Updated: 2018/02/06 14:44:09 by lportay          ###   ########.fr       */
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

int	read_state(t_21sh *env, t_line *l, t_key *key)
{
	if (*key->buf == NEWLINE_ || (env->emacs_mode && *key->buf == C_O))
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

void	linefunc_switch(t_21sh *env, t_line *l, t_key *key)
{
	t_line_pair	p[19];
	int			i;

	i = 0;
	init_line_funcs(p);
	while (p[i].test && !(p[i].test(env, l, key)))
		i++;
	if (p[i].test)
		p[i].func(env, l);
}

int	user_input(t_21sh *env, t_line *l, t_key *key)
{
	int ret;

	if (test_load_line(env, l, key) == true)
		load_line(env, l);
	update_line(env, l);

	if ((ret = read_state(env, l, key)) != READON)
		return (ret);

	if (ft_isprint(*key->buf))
		insert_char(key->buf, env, l);
	else
		linefunc_switch(env, l, key);

	if ((key->buf[0] && key->buf[0] != ESC) || (key->buf[1] && key->buf[1] != '[') || key->i == READLEN)
	{
		ft_bzero(key->buf, key->i);
		key->i = 0;
	}
//	else if (buf == C_R && env->history)
//		recherche dans l'historique (C_G + C_J + C_O)
//	else if (buf == TAB && env->autocomplete)
//		autocompletion
	return (READON);
}

void	query_linestate(t_dlist *dlst, t_stack **linestate)
{
	if ((*linestate)->state == BSLASH)
		stack_pop(linestate);
	while (dlst && (*linestate)->state != HASH)
	{
		update_linestate(linestate, *(char *)(dlst->content));
		if (*(char *)(dlst->content) != '\\' && (*linestate)->state == BSLASH)
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
		if (*(char *)l->split_line->content == '\\')
			ft_dlstremove(&l->split_line, &delvoid);
		l->line = l->line->next;
		ft_dlstdelone(&l->line->previous, &delvoid);
		l->line->previous = l->split_line;
		l->split_line->next = l->line;
		l->split_line = tmp;
	}
	else if (l->split_line && !l->line->next)
	{
		ft_dlstdelone(&l->line, &delvoid);
		tmp = l->split_line;
		ft_dlstend(&l->split_line);
		if (*(char *)l->split_line->content == '\\')
			ft_dlstremove(&l->split_line, &delvoid);
		l->split_line = tmp;
	}
	else if (!l->split_line)
		l->split_line = l->line;
}

void	err_quotes(t_line *l)
{
	write(STDIN_FILENO, "\n", 1);//
	dump_err(BADQUOTES);
	ft_dlstdel(&l->split_line, &delvoid);
	ft_dlstdel(&l->line, &delvoid);
	stack_del(&l->linestate);
}

void	wrap_lineread(t_21sh *env, t_line *l, char *prompt_mode)
{
	l->split_line = NULL;
	l->line_saved = false;
	ft_strcpy(env->prompt_mode, prompt_mode);
	stack_push(&l->linestate, stack_create(UNQUOTED));

	if (env->line_edition)
	{
		lineread(env, &env->line);
		while (l->linestate && l->linestate->state != UNQUOTED)
			lineread(env, &env->line);
	}
	else
	{
		getrawline(env, &env->line);
		while (l->linestate && l->linestate->state != UNQUOTED)
			getrawline(env, &env->line);
	}
	if (l->linestate)
		stack_del(&l->linestate);

	//DEBUG//
//	if (env->line.split_line)//
//		print_line(env->line.split_line->next);//print what's retrieved
//	write(1, "\n", 1);//
	/////////
}

