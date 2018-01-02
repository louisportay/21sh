/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 17:38:36 by lportay           #+#    #+#             */
/*   Updated: 2018/01/01 23:31:52 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	init_funcs(t_line_func *funcs)
{
	funcs[0] = LINE_FUNC(&test_upkey, &up_key);
	funcs[1] = LINE_FUNC(&test_downkey, &down_key);
	funcs[2] = LINE_FUNC(&test_lkey, &lkey);
	funcs[3] = LINE_FUNC(&test_rkey, &rkey);
	funcs[4] = LINE_FUNC(&test_del_current_char, &del_current_char);
	funcs[5] = LINE_FUNC(&test_del_previous_char, &del_previous_char);
	funcs[6] = LINE_FUNC(&test_line_beginning, &go_to_line_beginning);
	funcs[7] = LINE_FUNC(&test_line_end, &go_to_line_end);
	funcs[8] = LINE_FUNC(&test_lower_line, &go_lower_line);
	funcs[9] = LINE_FUNC(&test_upper_line, &go_upper_line);
	funcs[10] = LINE_FUNC(&test_go_prev_word, &go_to_previous_word);
	funcs[11] = LINE_FUNC(&test_go_next_word, &go_to_next_word);
	funcs[12] = LINE_FUNC(&test_kill_beginline, &kill_line_beginning);
	funcs[13] = LINE_FUNC(&test_kill_endline, &kill_line_end);
	funcs[14] = LINE_FUNC(&test_clear_screen, &clear_screen_);
	funcs[15] = LINE_FUNC(&test_yank, &yank);
	funcs[16] = LINE_FUNC(&test_emacs_mode, &reverse_emacs_mode);
	funcs[17] = LINE_FUNC(&test_killprevword, &kill_prev_word);
	funcs[18] = LINE_FUNC(NULL, NULL);
}

static int	user_input(t_21sh *env, char *buf, int *bufi)
{
	t_line_func	funcs[19];
	int			i;

	i = 0;
	init_funcs(funcs);	
	update_linemode(env);
	if (test_load_line(env, buf) == true)
		load_line(env);
	if (*buf == NEWLINE_ || (env->emacs_mode && *buf == C_O))
	{
		if (env->line && ft_dlstaddr(env->line, 0) != env->lastline)
			ft_dlstdel(&env->lastline, &delvoid);
		return (FINISHREAD);
	}
	else if (*buf == C_D && !ft_dlstcount(env->line))
	{
		if (env->linestate->state == UNQUOTED)
			return (EXITSHELL);
		else
			return (ERR_QUOTE);
	}
	else if (ft_isprint(*buf))
		insert_char(buf, env);
	else
	{
		while (funcs[i].test && funcs[i].test(env, buf, bufi) == false)
			i++;
		if (funcs[i].test)
			funcs[i].f(env);
	}
	if ((buf[0] && buf[0] != ESC) || (buf[1] && buf[1] != '[') || *bufi == READLEN)
	{
		ft_bzero(buf, *bufi);
		*bufi = 0;
	}

////	else if (!ft_strncmp(buf, M_D, ft_strlen(M_D)) && env->line->next && env->emacs_mode)
////		kill_next_word(env);

//	else if (buf == C_R && env->history)
//		recherche dans l'historique (C_G + C_J + C_O)
//	else if (buf == TAB && env->autocomplete)
//		autocompletion
	return (READON);
}

void	handle_bslash(t_stack **line)
{
	if ((*line)->state == BSLASH)
		stack_pop(line);
	else if ((*line)->state != SQUOTE)
		stack_push(line, stack_create(BSLASH));
}

void	handle_squote(t_stack **line)
{
	if ((*line)->state == SQUOTE)
		stack_pop(line);
	else if ((*line)->state != DQUOTE && (*line)->state != BSLASH)
		stack_push(line, stack_create(SQUOTE));
}

void	handle_dquote(t_stack **line)
{
	if ((*line)->state == DQUOTE)
		stack_pop(line);
	else if ((*line)->state != SQUOTE && (*line)->state != BSLASH)
		stack_push(line, stack_create(DQUOTE));
}

/*
void	handle_bquote(t_stack **line)
{
	if ((*line)->state == BQUOTE)
		stack_pop(line);
	else if ((*line)->state != SQUOTE && (*line)->state != BSLASH)
		stack_push(line, stack_create(BQUOTE));
}
*/

void	switch_state(t_stack **state, char c)
{
		if (c == '\\')
			handle_bslash(state);
		else if (c == '\'')
			handle_squote(state);
		else if (c == '\"')
			handle_dquote(state);
//		else if (c == '`')
//			handle_bquote(state);
}

void	query_linestate(t_dlist *dlst, t_stack **linestate)
{
	while (dlst)
	{
		switch_state(linestate, *(char *)(dlst->content));
		if (*(char *)(dlst->content) != '\\' && (*linestate)->state == BSLASH)
			stack_pop(linestate);
		dlst = dlst->next;
		}
}

void	join_split_lines(t_21sh *env)
{
	t_dlist *tmp;

	if (env->split_line && env->line->next)
	{
		tmp = env->split_line;
		ft_dlstend(&env->split_line);
		env->line = env->line->next;
		ft_dlstdelone(&env->line->previous, &delvoid);
		env->line->previous = env->split_line;
		env->split_line->next = env->line;
		env->split_line = tmp;
	}
	else if (env->split_line && !env->line->next)
		ft_dlstdelone(&env->line, &delvoid);
	else if (!env->split_line)
		env->split_line = env->line;
}

void	wrap_lineread(t_21sh *env)
{
	env->split_line = NULL;
	env->line_saved = false;
	env->prompt_mode = PS1;
	stack_push(&env->linestate, stack_create(UNQUOTED));
	lineread(env);
	while (env->linestate && env->linestate->state != UNQUOTED)
		lineread(env);
	if (env->linestate)
		stack_del(&env->linestate);

	//DEBUG//
	write(1, "\n", 1);//
	if (env->split_line)
		print_line(env->split_line->next);//print what's retrieved
	write(1, "\n", 1);//
	/////////
}

//change lineread return *eventually*

void		lineread(t_21sh *env)
{
	int		status;
	char	buf[READLEN];
	int		bufi;

	bufi = 0;
	status = READON;
	env->line = ft_dlstnew("HEAD", 5);
	env->lastline = env->line;
	env->cursor_offset = 0;
	env->multiline = false;
	print_prompt(env);
	env->line_len = env->cursor_offset;
	ft_bzero(buf, READLEN);
	if (env->linestate->state == BSLASH)
		stack_pop(&env->linestate);

	tputs(env->tc.im, 1, &ft_putchar_stdin);
	while (status == READON)
	{
		if (read(STDIN_FILENO, &buf[bufi++], 1) == -1)
			status = READERROR;
		else
			status = user_input(env, buf, &bufi);
	}
	tputs(env->tc.ei, 1, &ft_putchar_stdin);

	if (env->multiline == true)
		move_cursor_end_of_line(env);
	if (env->histlist)
		ft_dlsthead(&env->histlist);
	ft_dlsthead(&env->line);
	if (status == READERROR)
		fatal_err(FAILREAD, env);
	else if (status == EXITSHELL)
		wrap_exit(EXIT_SUCCESS, env);
	else if (status == ERR_QUOTE)
	{
		write(STDIN_FILENO, "\n", 1);
		dump_err(BADQUOTES);
		ft_dlstdel(&env->split_line, &delvoid);
		ft_dlstdel(&env->line, &delvoid);
		stack_del(&env->linestate);
		return ;
	}

	query_linestate(env->line->next, &env->linestate);

	if (env->linestate->state != UNQUOTED)
	{
		if ((env->cursor_offset % env->ws.ws_col))
			write(STDIN_FILENO, "\n", 1);
		env->prompt_mode = PS2;
	}

	join_split_lines(env);

	if (env->history && env->split_line->next && env->linestate->state == UNQUOTED && dlst_isonlywhitespace(env->split_line->next) == false)
	{
		add_histentry(env);
		env->line_saved = true; 
	}

	ft_dlstaddend(env->split_line, (env->final_newline = ft_dlstnew("\n", 1)));

}
