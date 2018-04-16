/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paren.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 13:22:28 by lportay           #+#    #+#             */
/*   Updated: 2018/04/10 11:25:25 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	handle_paren(t_stack **line, char c)
{
	if ((*line)->state == PAREN && c == ')')
		stack_pop(line);
	else if ((*line)->state != BSLASH && (*line)->state != SQUOTE
			&& (*line)->state != DQUOTE && c == '(')
		if (stack_create_push(line, PAREN) == -1)
			fatal_err(NOMEM, get_ctxaddr());
}

void	handle_brace(t_stack **line, char c)
{
	if ((*line)->state & BRACE && c == '}')
		stack_pop(line);
	else if ((*line)->state & DOLLAR && c == '{')
		(*line)->state |= BRACE;
	else if ((*line)->state != BSLASH && (*line)->state != SQUOTE
			&& (*line)->state != DQUOTE && c == '{')
		if (stack_create_push(line, BRACE) == -1)
			fatal_err(NOMEM, get_ctxaddr());
}

void	handle_dollar(t_stack **line)
{
	if ((*line)->state != SQUOTE && (*line)->state != BSLASH)
		if (stack_create_push(line, DOLLAR) == -1)
			fatal_err(NOMEM, get_ctxaddr());
}
