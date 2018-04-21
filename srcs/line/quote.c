/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 14:26:41 by lportay           #+#    #+#             */
/*   Updated: 2018/04/21 13:14:29 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static void	handle_bslash(t_stack **line)
{
	if ((*line)->state == BSLASH)
		stack_pop(line);
	else if ((*line)->state != SQUOTE)
		if (stack_create_push(line, BSLASH) == -1)
			fatal_err(NOMEM, get_ctxaddr());
}

static void	handle_squote(t_stack **line)
{
	if ((*line)->state == SQUOTE)
		stack_pop(line);
	else if ((*line)->state != DQUOTE && (*line)->state != BSLASH)
		if (stack_create_push(line, SQUOTE) == -1)
			fatal_err(NOMEM, get_ctxaddr());
}

static void	handle_dquote(t_stack **line)
{
	if ((*line)->state == DQUOTE)
		stack_pop(line);
	else if ((*line)->state != SQUOTE && (*line)->state != BSLASH)
		if (stack_create_push(line, DQUOTE) == -1)
			fatal_err(NOMEM, get_ctxaddr());
}

/*
** static void	handle_bquote(t_stack **line)
** {
** 	if ((*line)->state == BQUOTE)
** 		stack_pop(line);
** 	else if ((*line)->state != SQUOTE && (*line)->state != BSLASH)
** 	if (stack_create_push(line, BQUOTE) == -1)
** 		fatal_err(NOMEM, get_ctxaddr());
** }
**
**	else if (c == '`')
**		handle_bquote(state);
*/

void		update_linestate(t_stack **state, char c)
{
	if (c == '\\')
		handle_bslash(state);
	else if (c == '\'')
		handle_squote(state);
	else if (c == '\"')
		handle_dquote(state);
	else if (c == '#')
		handle_hash(state);
	else if (c == '(' || c == ')')
		handle_paren(state, c);
	else if (c == '{' || c == '}')
		handle_brace(state, c);
	else if (c == '$')
		handle_dollar(state);
}
