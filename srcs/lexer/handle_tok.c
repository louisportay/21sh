/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tok.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 21:00:46 by lportay           #+#    #+#             */
/*   Updated: 2018/03/19 11:15:05 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Returns 1 if token has been extended
*/

int		extend_word(t_token *token, char c, int quote_state)
{
	if (token->type == IO_NUMBER && ((!ft_isdigit(c) && c != '<' && c != '>') ||
				quote_state != UNQUOTED))
		token->type = WORD;
	if (((is_metachar(c)) && quote_state == UNQUOTED) ||
			(c == '#' && quote_state == HASH))
		return (0);
	else if (token->type == WORD && c == '=')
		token->type = ASSIGNMENT_WORD;
	return (1);
}

/*
** Returns true if the operator has been extended,
** Otherwise returns false indicating that the token shall be delimited
*/

int		extend_operator(t_token *token, char c, int quote_state)
{
	if (quote_state != UNQUOTED || ft_isblank(c))
		return (0);

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
		return (0);
	return (1);
}


int		token_type(char c, int quote_state)
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
