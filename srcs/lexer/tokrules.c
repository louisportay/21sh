/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokrules.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 21:07:17 by lportay           #+#    #+#             */
/*   Updated: 2018/03/18 15:24:01 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** '`' 42SH
** c == '`' ||
*/

//tej les parentheses
int		is_quoting(char c)
{
	if (c == '\\' ||
		c == '\'' ||
		c == '"' ||
		c == '#' ||
		c == '(' ||
		c == ')' ||
		c == '{' ||
		c == '}')
		return (1);
	return (0);
}

int	is_metachar(char c)
{
	if (c == '|' || c == '&' || c == ';' || c == '<' || c == '>')// || ft_isblank(c))
		return (1);
	return (0);
}

/*
** Returns true if token has been extended
*/

bool	extend_word(t_token *token, char c, int quote_state)
{
	if (token->type == IO_NUMBER && ((!ft_isdigit(c) && c != '<' && c != '>') || quote_state != UNQUOTED))
		token->type = WORD;
	if (((ft_isblank(c) == true || is_metachar(c)) && quote_state == UNQUOTED) || (c == '#' && quote_state == HASH))
		return (false);
	else if (token->type == WORD && c == '=')
		token->type = ASSIGNMENT_WORD;
	return (true);
}

/*
** Returns true if the operator has been extended,
** Otherwise returns false indicating that the token shall be delimited
*/

bool	extend_operator(t_token *token, char c, int quote_state)
{
	if (quote_state != UNQUOTED || ft_isblank(c) == true)
		return (false);

	if (token->type & OR && c == '|')
		token->type = OR_IF;
	else if (token->type & AND && c == '&')
		token->type = AND_IF;
	else if (token->type & AND && c == '>')
		token->type = ANDGREAT;
	else if (token->type & LESS && c == '<')
		token->type = DLESS;
	else if (token->type & LESS && c == '&')
		token->type = LESSAND;
	else if (token->type & GREAT && c == '>')
		token->type = DGREAT;
	else if (token->type & GREAT && c == '&')
		token->type = GREATAND;
	else if (token->type & DLESS && c == '<')
		token->type = TLESS;
	else if (token->type & ANDGREAT && c == '>')
		token->type = ANDDGREAT;
	else
		return (false);
	return (true);
}


int		basic_token_type(char c, int quote_state)
{
	if (c == '\n')
		return (NEWLINE);
	else if (c == '#' && quote_state == HASH)
		return (COMMENT);
	else if (quote_state != UNQUOTED)
		return (WORD);
	else if (c == ';')
		return (SEMICOL);
	else if (c == '|')
		return (OR);
	else if (c == '&')
		return (AND);
	else if (c == '<')
		return (LESS);
	else if (c == '>')
		return (GREAT);
	else if (ft_isdigit(c) == true)
		return (IO_NUMBER);
	else
		return (WORD);
}

void	create_dash_token(t_token *last_tok, t_dlist *line)
{
	last_tok->next = new_token(line->next);
	last_tok->next->type = WORD;
	last_tok->next->last_letter = line->next;
}

int		is_max_operator(int n)
{
		if (n & (OR_IF | AND_IF |
			DGREAT | LESSAND | GREATAND | ANDDGREAT | TLESS |
			NEWLINE | SEMICOL))
			return (1);
		return (0);
}

int		is_extendable_operator(int n)
{
		if (n & (OR | AND | LESS | GREAT | DLESS | ANDGREAT))
			return (1);
		return (0);
}

void		tokrules(t_token *last_tok, t_dlist *line, t_stack **quote)
{
	if (!line->next)
	{
		if (!last_tok->last_letter)
			last_tok->last_letter = line->prev;
		if (last_tok->type == IO_NUMBER)
			last_tok->type = WORD;
		last_tok->next = new_token(line);
		last_tok->next->type = NEWLINE;
		last_tok->next->last_letter = line; 
		return ;
	}

	if (is_quoting(*(char *)line->data))
		update_linestate(quote, *(char *)line->data);

	if (*(char *)line->data == '\n' && ((*quote)->state != BSLASH && (*quote)->state != DQUOTE && (*quote)->state != SQUOTE))
	{
		last_tok->last_letter = line->prev;
		if (last_tok->type == COMMENT)
			stack_pop(quote);
	}

	if (!last_tok->last_letter && (last_tok->type & (WORD | ASSIGNMENT_WORD | IO_NUMBER)))
		if (!(extend_word(last_tok, *(char *)line->data, (*quote)->state)))
				last_tok->last_letter = line->prev;

	if (!last_tok->last_letter && is_extendable_operator(last_tok->type))
		if (!(extend_operator(last_tok, *(char *)line->data, (*quote)->state)))
				last_tok->last_letter = line->prev;

	if (last_tok->last_letter && (!(ft_isblank(*(char *)line->data)) || (*quote)->state != UNQUOTED) && last_tok->last_letter != line)
	{
		last_tok->next = new_token(line);
		last_tok->next->type = basic_token_type(*(char *)line->data, (*quote)->state);
		if (is_max_operator(last_tok->next->type))
			last_tok->next->last_letter = line;
	}

	if (is_max_operator(last_tok->type) && !last_tok->last_letter)
	{
		last_tok->last_letter = line;
		if (*(char *)line->next->data == '-' && (last_tok->type & (LESSAND | GREATAND)))
			create_dash_token(last_tok, line);
	}

	if ((*quote)->state == BSLASH && *(char *)line->data != '\\')
			stack_pop(quote);
}
