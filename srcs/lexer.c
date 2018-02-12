/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 09:42:08 by lportay           #+#    #+#             */
/*   Updated: 2018/02/12 12:42:41 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*token_str(t_token *tok)
{
	char 	*head;
	char	*s;
	t_dlist	*tmp;
	size_t	len;

	len = 1;
	tmp = tok->first_letter;
	while (tmp != tok->last_letter)
	{
		len++;
		tmp = tmp->next;
	}
	if (!(s = ft_strnew(len + 1)))
		return (NULL);
	head = s;
	while (tok->first_letter != tok->last_letter)
	{
		*s++ = *(char *)tok->first_letter->data;
		tok->first_letter = tok->first_letter->next;
	}
	*s++ = *(char *)tmp->data;
	*s = '\0';
	return (head);
}

void	dump_token(t_token *tok)
{
	t_dlist *tmp;

	tmp = tok->first_letter;
	while (tmp != tok->last_letter)
	{
		write(STDOUT_FILENO, tmp->data, 1);
		tmp = tmp->next;
	}
	write(STDOUT_FILENO, tmp->data, 1);
}

void	init_token_table(t_keyval *tok)
{
	tok[0] = KEY_VAL(NEWLINE, "NEWLINE");
	tok[1] = KEY_VAL(SEMICOL, "SEMICOL");
	tok[2] = KEY_VAL(IO_NUMBER, "IO_NUMBER");
	tok[3] = KEY_VAL(WORD, "WORD");
	tok[4] = KEY_VAL(ASSIGNMENT_WORD, "ASSIGNMENT_WORD");
	tok[5] = KEY_VAL(OR, "OR");
	tok[6] = KEY_VAL(AND, "AND");
	tok[7] = KEY_VAL(LESS, "LESS");
	tok[8] = KEY_VAL(GREAT, "GREAT");
	tok[9] = KEY_VAL(OR_IF, "OR_IF");
	tok[10] = KEY_VAL(AND_IF, "AND_IF");
	tok[11] = KEY_VAL(DLESS, "DLESS");
	tok[12] = KEY_VAL(DGREAT, "DGREAT");
	tok[13] = KEY_VAL(LESSAND, "LESSAND");
	tok[14] = KEY_VAL(GREATAND, "GREATAND");
	tok[15] = KEY_VAL(TLESS, "TLESS");
	tok[16] = KEY_VAL(ANDGREAT, "ANDGREAT");
	tok[17] = KEY_VAL(ANDDGREAT, "ANDDGREAT");
	tok[18] = KEY_VAL(DOLLAR, "DOLLAR");
	tok[19] = KEY_VAL(BANG, "BANG");
	tok[20] = KEY_VAL(PARAM_EXP, "PARAM_EXP");
	tok[21] = KEY_VAL(CMD_SUB, "CMD_SUB");
	tok[22] = KEY_VAL(ARI_EXP, "ARI_EXP");
	tok[23] = KEY_VAL(COMMENT, "COMMENT");
	tok[24] = KEY_VAL(0, NULL);
}

void	print_toklist(t_token *toklist)
{
	t_keyval	tok[25];
	int			i;

	init_token_table(tok);
	while (toklist)
	{
		dump_token(toklist);
		ft_putstr(" Type: ");
		i = 0;
		while ((unsigned)tok[i].key != toklist->type && tok[i].key)
				i++;
		ft_putstr(tok[i].val);
		write(STDOUT_FILENO, "\n", 1);
		toklist = toklist->next;
	}
}

/*
** '`' 42SH
*/

bool	is_quote_hash_paren(char c)
{
	if (c == '\'' || c == '\\' || c == '"' || c == '#' || c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']')
		return (true);
	else
		return (false);
}

/*
** POSIX blank
*/

int 	ft_isblank(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	else
		return (false);
}

bool	is_delimiter(char c)
{
	if (c == '|' || c == '&' || c == ';' || c == '<' || c == '>' || c == '$' || c == '!')
		return (true);
	else
		return (false);
}

/*
** Returns true if token has been extended
*/

bool	extend_word(t_token *token, char c, int quote_state)
{
	if (token->type == IO_NUMBER && ((!ft_isdigit(c) && c != '<' && c != '>') || quote_state != UNQUOTED))
		token->type = WORD;
	if (((ft_isblank(c) == true || is_delimiter(c)) && quote_state == UNQUOTED) || (c == '#' && quote_state == HASH))
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
	else if (c == '$')
		return (DOLLAR);
	else if (c == '!')
		return (BANG);
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
		if (ISREDIR(tmp->type))
			free(((t_redir *)tmp)->s_rhs);
		free(tmp);
		tmp = *toklist;
	}
	*toklist = NULL;
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
			last_tok->last_letter = line->prev;
		if (last_tok->type == IO_NUMBER)
			last_tok->type = WORD;
		last_tok->next = new_token(line);
		last_tok->next->type = NEWLINE;
		last_tok->next->last_letter = line; 
		return ;
	}

	if (is_quote_hash_paren(*(char *)line->data) == true)
		update_linestate(quote, *(char *)line->data);

	if (*(char *)line->data == '\n' && ((*quote)->state != BSLASH && (*quote)->state != DQUOTE && (*quote)->state != SQUOTE))
	{
		last_tok->last_letter = line->prev;
		if (last_tok->type == COMMENT)
			stack_pop(quote);
	}

	if (!last_tok->last_letter && IS_WORD_IO_NUMBER(last_tok->type))
		if (!(extend_word(last_tok, *(char *)line->data, (*quote)->state)))
				last_tok->last_letter = line->prev;

	if (!last_tok->last_letter && IS_NOT_MAX_OPE(last_tok->type))
		if (!(extend_operator(last_tok, *(char *)line->data, (*quote)->state)))
				last_tok->last_letter = line->prev;

	if (last_tok->last_letter && (!(ft_isblank(*(char *)line->data)) || (*quote)->state != UNQUOTED) && last_tok->last_letter != line)
	{
		last_tok->next = new_token(line);
		last_tok->next->type = basic_token_type(*(char *)line->data, (*quote)->state);
		if (IS_MAX_OPE(last_tok->next->type))
			last_tok->next->last_letter = line;
	}

	if (IS_MAX_OPE(last_tok->type) && !last_tok->last_letter)
	{
		last_tok->last_letter = line;
		if (*(char *)line->next->data == '-' && (last_tok->type & (LESSAND | GREATAND)))
			create_dash_token(last_tok, line);
	}

	if ((*quote)->state == BSLASH && *(char *)line->data != '\\')
			stack_pop(quote);
}

void	delete_following_redir(t_token *toklist)
{
	while (toklist)
	{
		if (ISREDIR(toklist->type))
			toklist->type = WORD;
		toklist = toklist->next;
	}
}

void	requalify_tokens(t_token **toklist)
{
	t_keyval	tok[25];
	t_token		*ret;
	int			i;

	if ((ret = filter_tokens(*toklist)) != SUCCESS)
	{
		i = 0;
		init_token_table(tok);
		while ((unsigned)tok[i].key != ret->type && tok[i].key)
				i++;
		ft_putstr_fd("syntax error near token `", STDERR_FILENO);
		ft_putstr_fd(tok[i].val, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		delete_following_redir(ret);
		delete_toklist(toklist);
	}
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

//	print_toklist(toklist->next);//
//	write(STDOUT_FILENO, "\n", 1);//
	requalify_tokens(&toklist);
//	if (toklist)//
//		print_toklist(toklist->next);//
	stack_del(&quote_state);

	return (toklist);
}
