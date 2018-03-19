/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokrules.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 21:07:17 by lportay           #+#    #+#             */
/*   Updated: 2018/03/19 11:14:33 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		create_last_tok(t_token *last_tok, t_dlist *line)
{
	if (!last_tok->last_letter)
		last_tok->last_letter = line->prev;
	if (last_tok->type == IO_NUMBER)
		last_tok->type = WORD;
	last_tok->next = new_token(line);
	last_tok->next->type = NEWLINE;
	last_tok->next->last_letter = line; 
}

void	quoting_newline(t_token *last_tok, t_dlist *line, t_stack **quote)
{
	if (is_quoting(*(char *)line->data))
		update_linestate(quote, *(char *)line->data);

	if (*(char *)line->data == '\n' && !((*quote)->state & (BSLASH | DQUOTE | SQUOTE)))
	{
		last_tok->last_letter = line->prev;
		if (last_tok->type == COMMENT)
			stack_pop(quote);
	}
}

void		delimit_tokens(t_token *last_tok, t_dlist *line, t_stack **quote)
{
	if (!last_tok->last_letter && (last_tok->type & (WORD | ASSIGNMENT_WORD |
IO_NUMBER)) && !(extend_word(last_tok, *(char *)line->data, (*quote)->state)))
		last_tok->last_letter = line->prev;
	if (!last_tok->last_letter && is_extendable_operator(last_tok->type)
			&& !(extend_operator(last_tok, *(char *)line->data, (*quote)->state)))
		last_tok->last_letter = line->prev;
	if (last_tok->last_letter && (!(ft_isblank(*(char *)line->data)) ||
				(*quote)->state != UNQUOTED) && last_tok->last_letter != line)
	{
		last_tok->next = new_token(line);
		last_tok->next->type = token_type(*(char *)line->data, (*quote)->state);
		if (is_max_operator(last_tok->next->type))
			last_tok->next->last_letter = line;
	}
	if (is_max_operator(last_tok->type) && !last_tok->last_letter)
	{
		last_tok->last_letter = line;
		if (*(char *)line->next->data == '-' && (last_tok->type &
					(LESSAND | GREATAND)))
		{
			last_tok->next = new_token(line->next);
			last_tok->next->type = WORD;
			last_tok->next->last_letter = line->next;
		}
	}
}

void		tokrules(t_token *last_tok, t_dlist *line, t_stack **quote)
{
	if (!line->next)
		return (create_last_tok(last_tok, line));

	quoting_newline(last_tok, line, quote);
	delimit_tokens(last_tok, line, quote);
	if ((*quote)->state == BSLASH && *(char *)line->data != '\\')
			stack_pop(quote);
}
