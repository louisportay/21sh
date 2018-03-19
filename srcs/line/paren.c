/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paren.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 13:22:28 by lportay           #+#    #+#             */
/*   Updated: 2018/03/19 13:24:55 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	handle_paren(t_stack **line, char c)
{
	if ((*line)->state == PAREN && c == ')')
		stack_pop(line);
	else if ((*line)->state != BSLASH && (*line)->state != SQUOTE
			&& (*line)->state != DQUOTE && c == '(')
		stack_push(line, stack_create(PAREN));
}

void	handle_brace(t_stack **line, char c)
{
	if ((*line)->state == BRACE && c == '}')
		stack_pop(line);
	else if ((*line)->state != BSLASH && (*line)->state != SQUOTE
			&& (*line)->state != DQUOTE && c == '{')
		stack_push(line, stack_create(BRACE));
}

void	handle_hash(t_stack **line)
{
	if ((*line)->state == UNQUOTED || (*line)->state == PAREN
			|| (*line)->state == BRACE)
		stack_push(line, stack_create(HASH));
}
