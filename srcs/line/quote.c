/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 14:26:41 by lportay           #+#    #+#             */
/*   Updated: 2018/04/06 19:44:30 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	handle_bslash(t_stack **line)
{
	if ((*line)->state == BSLASH)
		stack_pop(line);
	else if ((*line)->state != SQUOTE)
		stack_push(line, stack_create(BSLASH));
}

static void	handle_squote(t_stack **line)
{
	if ((*line)->state == SQUOTE)
		stack_pop(line);
	else if ((*line)->state != DQUOTE && (*line)->state != BSLASH)
		stack_push(line, stack_create(SQUOTE));
}

static void	handle_dquote(t_stack **line)
{
	if ((*line)->state == DOLLAR)
		stack_pop(line);
	if ((*line)->state == DQUOTE)
		stack_pop(line);
	else if ((*line)->state != SQUOTE && (*line)->state != BSLASH)
		stack_push(line, stack_create(DQUOTE));
}

/*
** 42SH
*/

/*
** void	handle_bquote(t_stack **line)
** {
** 	if ((*line)->state == BQUOTE)
** 		stack_pop(line);
** 	else if ((*line)->state != SQUOTE && (*line)->state != BSLASH)
** 		stack_push(line, stack_create(BQUOTE));
** }
**
**	else if (c == '`')
**		handle_bquote(state);
*/

void		update_linestate(t_stack **state, char c)
{
	if (c == '#')
		handle_hash(state);
	else if (c == '\\')
		handle_bslash(state);
	else if (c == '\'')
		handle_squote(state);
	else if (c == '\"')
		handle_dquote(state);
	else if (c == '(' || c == ')')
		handle_paren(state, c);
	else if (c == '{' || c == '}')
		handle_brace(state, c);
	else if (c == '$')
		handle_dollar(state);
}
