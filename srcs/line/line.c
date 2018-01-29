/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 17:38:36 by lportay           #+#    #+#             */
/*   Updated: 2018/01/29 20:34:59 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	init_line_funcs(t_line_func *funcs)
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
	//funcs[18] = LINE_FUNC(&test_killnextword, &kill_next_word);
	funcs[18] = LINE_FUNC(NULL, NULL);
}

int	user_input(t_21sh *env, char *buf, int *bufi)
{
	t_line_func	funcs[19];
	int			i;

	i = 0;
	init_line_funcs(funcs);	
	update_linemode(&env->line);
	if (test_load_line(env, buf) == true)
		load_line(env);
	if (*buf == NEWLINE_ || (env->emacs_mode && *buf == C_O))
	{
		if (env->line.line && ft_dlstaddr(env->line.line, 0) != env->line.lastline)
			ft_dlstdel(&env->line.lastline, &delvoid);
		return (FINISHREAD);
	}
	else if (*buf == C_D && !ft_dlstcount(env->line.line))
	{
		if (env->line.linestate->state == UNQUOTED)
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
/*static*/ void	handle_bslash(t_stack **line)
{
	if ((*line)->state == BSLASH)
		stack_pop(line);
	else if ((*line)->state != SQUOTE)
		stack_push(line, stack_create(BSLASH));
}

/*static*/ void	handle_squote(t_stack **line)
{
	if ((*line)->state == SQUOTE)
		stack_pop(line);
	else if ((*line)->state != DQUOTE && (*line)->state != BSLASH)
		stack_push(line, stack_create(SQUOTE));
}

/*static*/ void	handle_dquote(t_stack **line)
{
	if ((*line)->state == DQUOTE)
		stack_pop(line);
	else if ((*line)->state != SQUOTE && (*line)->state != BSLASH)
		stack_push(line, stack_create(DQUOTE));
}

/*static*/ void	handle_paren(t_stack **line, char c)
{
	if ((*line)->state == PAREN && c == ')')
		stack_pop(line);
	else if ((*line)->state != BSLASH && (*line)->state != SQUOTE && (*line)->state != DQUOTE && c == '(')
		stack_push(line, stack_create(PAREN));
}

void	handle_brace(t_stack **line, char c)
{
	if ((*line)->state == BRACE && c == '}')
		stack_pop(line);
	else if ((*line)->state != BSLASH && (*line)->state != SQUOTE && (*line)->state != DQUOTE && c == '{')
		stack_push(line, stack_create(BRACE));
}

void	handle_bracket(t_stack **line, char c)
{
	if ((*line)->state == BRACKET && c == ']')
		stack_pop(line);
	else if ((*line)->state != BSLASH && (*line)->state != SQUOTE && (*line)->state != DQUOTE && c == '[')
		stack_push(line, stack_create(BRACKET));
}

void handle_hash(t_stack **line)
{
	if ((*line)->state == UNQUOTED || (*line)->state == PAREN || (*line)->state == BRACE || (*line)->state == BRACKET)
		stack_push(line, stack_create(HASH));
}

/*
** 42SH
*/

/*
void	handle_bquote(t_stack **line)
{
	if ((*line)->state == BQUOTE)
		stack_pop(line);
	else if ((*line)->state != SQUOTE && (*line)->state != BSLASH)
		stack_push(line, stack_create(BQUOTE));
}
*/

void	update_linestate(t_stack **state, char c)
{
	if (c == '#')
		handle_hash(state);
	else if (c == '\\')
		handle_bslash(state);
	else if (c == '\'')
		handle_squote(state);
	else if (c == '\"')
		handle_dquote(state);
//	else if (c == '`')
//		handle_bquote(state);
	else if (c == '(' || c == ')')
		handle_paren(state, c);
	else if (c == '{' || c == '}')
		handle_brace(state, c);
	else if (c == '[' || c == ']')
		handle_bracket(state, c);
}

void	query_linestate(t_dlist *dlst, t_stack **linestate)
{
	while (dlst && (*linestate)->state != HASH)
	{
		update_linestate(linestate, *(char *)(dlst->content));
		if (*(char *)(dlst->content) != '\\' && (*linestate)->state == BSLASH)
			stack_pop(linestate);
		dlst = dlst->next;
		}
}

void	join_split_lines(t_line *line)
{
	t_dlist *tmp;

	if (line->split_line && line->line->next)
	{
		tmp = line->split_line;
		ft_dlstend(&line->split_line);
		if (*(char *)line->split_line->content == '\\')
			ft_dlstremove(&line->split_line, &delvoid);
		line->line = line->line->next;
		ft_dlstdelone(&line->line->previous, &delvoid);
		line->line->previous = line->split_line;
		line->split_line->next = line->line;
		line->split_line = tmp;
	}
	else if (line->split_line && !line->line->next)
	{
		ft_dlstdelone(&line->line, &delvoid);
		tmp = line->split_line;
		ft_dlstend(&line->split_line);
		if (*(char *)line->split_line->content == '\\')
			ft_dlstremove(&line->split_line, &delvoid);
		line->split_line = tmp;
	}
	else if (!line->split_line)
		line->split_line = line->line;
}

void	err_quotes(t_line *line)
{
		write(STDIN_FILENO, "\n", 1);
		dump_err(BADQUOTES);
		ft_dlstdel(&line->split_line, &delvoid);
		ft_dlstdel(&line->line, &delvoid);
		stack_del(&line->linestate);
}

void	wrap_lineread(t_21sh *env)
{
	env->line.split_line = NULL;
	env->line.line_saved = false;
	ft_strcpy(env->prompt_mode, PS1);
	stack_push(&env->line.linestate, stack_create(UNQUOTED));
	
	if (env->line_edition == true)
	{
		lineread(env, &env->line);
		while (env->line.linestate && env->line.linestate->state != UNQUOTED)
			lineread(env, &env->line);
	}
	else
		wrap_getrawline(env);

	if (env->line.linestate)
		stack_del(&env->line.linestate);

	//DEBUG//
	write(1, "\n", 1);//

	if (env->line.split_line)
		print_line(env->line.split_line->next);//print what's retrieved
	write(1, "\n", 1);//
	/////////
}

