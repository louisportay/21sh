/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 14:26:41 by lportay           #+#    #+#             */
/*   Updated: 2018/03/18 18:46:06 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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

//void	handle_paren(t_stack **line, char c)
//{
//	if ((*line)->state == PAREN && c == ')')
//		stack_pop(line);
//	else if ((*line)->state != BSLASH && (*line)->state != SQUOTE && (*line)->state != DQUOTE && c == '(')
//		stack_push(line, stack_create(PAREN));
//}
//
//void	handle_brace(t_stack **line, char c)
//{
//	if ((*line)->state == BRACE && c == '}')
//		stack_pop(line);
//	else if ((*line)->state != BSLASH && (*line)->state != SQUOTE && (*line)->state != DQUOTE && c == '{')
//		stack_push(line, stack_create(BRACE));
//}

void handle_hash(t_stack **line)
{
	if ((*line)->state == UNQUOTED)// || (*line)->state == PAREN || (*line)->state == BRACE)
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

//tej les paren + braces

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
//	else if (c == '(' || c == ')')
//		handle_paren(state, c);
//	else if (c == '{' || c == '}')
//		handle_brace(state, c);
}
