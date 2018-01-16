/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 09:42:08 by lportay           #+#    #+#             */
/*   Updated: 2018/01/16 18:08:10 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"


void	print_toklist(t_token *toklist)
{
	while (toklist)
	{
		ft_putstr("First Letter: \'");
		write(STDOUT_FILENO, (char *)toklist->first_letter->content, 1);
		ft_putstr("\' Last Letter: \'");
		write(STDOUT_FILENO, (char *)toklist->last_letter->content, 1);
		ft_putstr("\' Type: ");
		ft_putnbr(toklist->type);
		write(STDOUT_FILENO, "\n", 1);
		
		toklist = toklist->next;
	}
}


bool	isquote(char c)
{
	if (c == '\'' || c == '\\' || c == '"')
		return (true);
	else
		return (false);
}

bool 	ft_isblank(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	else
		return (false);
}

bool	is_simple_operator(char c)
{
	if (c == '|' || c == '&' || c == ';' || c == '<' || c == '>')
		return (true);
	else
		return (false);
}

bool is_word_operator(int type)
{
	if (type == WORD || type == ASSIGNMENT_WORD || type == IO_NUMBER)
		return (true);
	else
		return (false);
}

bool is_maximum_operator(int type)
{
	if (type == OR_IF || type == AND_IF || type == DLESS || type == DGREAT || type == LESSAND || type == GREATAND)
		return (true);
	else
		return (false);
}

bool is_extendable_operator(int type)
{
	if (type == OR || type == AND || type == LESS || type == GREAT)
		return (true);
	else
		return (false);
}

// returns true if token has been extended

bool	extend_word(t_token *token, char c, int quote_state)
{
	if (token->type == IO_NUMBER && ((!ft_isdigit(c) && c != '<' && c != '>') || quote_state != UNQUOTED))
		token->type = WORD;
	if ((ft_isblank(c) == true || is_simple_operator(c)) && quote_state == UNQUOTED)
		return (false);
	else if (token->type == WORD && c == '=')
		token->type = ASSIGNMENT_WORD;
	return (true);
}
		
// Returns true if the operator has been extended

bool	extend_operator(t_token *token, char c, int quote_state)
{
	if (quote_state != UNQUOTED || ft_isblank(c) == true)
			return (false);

		if (token->type == OR && c == '|')
			token->type = OR_IF;
		else if (token->type == AND && c == '&')
			token->type = AND_IF;
		else if (token->type == LESS && c == '<')
			token->type = DLESS;
		else if (token->type == LESS && c == '&')
			token->type = LESSAND;
		else if (token->type == GREAT && c == '>')
			token->type = DGREAT;
		else if (token->type == GREAT && c == '&')
			token->type = GREATAND;
		else
			return (false);
	return (true);
}


int		basic_token_type(char c, int quote_state)
{
	if (c == '\n')
		return (NEWLINE);
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

void	delete_toklist(t_token **toklist)
{
	t_token *tmp;

	tmp = *toklist;
	while (tmp)
	{
		*toklist = (*toklist)->next;
		free(tmp);
		tmp = *toklist;
	}
	*toklist = NULL;
}

/*
** Replace ASSIGNMENT_WORD by WORD when character in the part before the '=' sign does not respect the NAME Posix rule
*/

void	check_assignment_words(t_token *toklist)
{
	t_dlist *tmp;

	while (toklist)
	{
		if (toklist->type == ASSIGNMENT_WORD)
		{
			tmp = toklist->first_letter;
			if (ft_isdigit(*(char *)tmp->content) == true)
					toklist->type = WORD;
			while (tmp != toklist->last_letter && toklist->type == ASSIGNMENT_WORD)
			{
				if (ft_isalnum(*(char *)tmp->content) == false && *(char *)tmp->content != '_')
					toklist->type = WORD;
				tmp = tmp->next;
			}
		}
		toklist = toklist->next;
	}
}

void	replace_and_token(t_token *toklist)
{
	while (toklist)
	{
		if (toklist->type == AND)
			toklist->type = WORD;
		toklist = toklist->next;
	}
}

t_token		*new_token(t_dlist *line)
{
	t_token *new;

	if (!(new = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
	new->first_letter = line;
	new->last_letter = NULL;
	new->next = NULL;
	return (new);
}

void	create_dash_token(t_token *last_tok, t_dlist *line)
{
	last_tok->next = new_token(line->next);
	last_tok->next->type = WORD;
	last_tok->next->last_letter = line->next;
}

void		apply_tokrules(t_token *last_tok, t_dlist *line, t_stack **quote)
{
	if (!line->next)
	{
		if (!last_tok->last_letter)
			last_tok->last_letter = line->previous;
		if (last_tok->type == IO_NUMBER)
			last_tok->type = WORD;
		last_tok->next = new_token(line);
		last_tok->next->type = NEWLINE;
		last_tok->next->last_letter = line; 
		return ;
	}

	if (isquote(*(char *)line->content) == true)
		switch_state(quote, *(char *)line->content);

	if (!last_tok->last_letter && is_word_operator(last_tok->type))
		if (!(extend_word(last_tok, *(char *)line->content, (*quote)->state)))
				last_tok->last_letter = line->previous;

	if (!last_tok->last_letter && is_extendable_operator(last_tok->type))
		if (!(extend_operator(last_tok, *(char *)line->content, (*quote)->state)))
				last_tok->last_letter = line->previous;
		
	if (last_tok->last_letter && (!(ft_isblank(*(char *)line->content)) || (*quote)->state != UNQUOTED) && last_tok->last_letter != line)
	{
		last_tok->next = new_token(line);
		last_tok->next->type = basic_token_type(*(char *)line->content, (*quote)->state);
		if (last_tok->next->type == SEMICOL)
			last_tok->next->last_letter = line;
	}

	if (is_maximum_operator(last_tok->type) && !last_tok->last_letter)
	{
		last_tok->last_letter = line;
		if (*(char *)line->next->content == '-' && (last_tok->type == LESSAND || last_tok->type == GREATAND))
			create_dash_token(last_tok, line);
	}

	if ((*quote)->state == BSLASH && *(char *)line->content != '\\')
			stack_pop(quote);
}

t_token		*tokenizer(t_dlist *line)
{
	t_token *toklist;
	t_token *last_tok;
	t_stack *quote_state;

	quote_state = NULL;
	stack_push(&quote_state, stack_create(UNQUOTED));

	toklist = new_token(line);
	toklist->last_letter = line;
	toklist->type = HEAD;

	last_tok = toklist;
	
	line = line->next;
	while (line)
	{
		apply_tokrules(last_tok, line, &quote_state);
		line = line->next;
		if (last_tok->next)
			last_tok = last_tok->next;
	}
	check_assignment_words(toklist->next);
	replace_and_token(toklist->next);
//	print_toklist(toklist->next);//
	stack_del(&quote_state);

	return (toklist);
}
