/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 09:42:08 by lportay           #+#    #+#             */
/*   Updated: 2018/02/12 14:06:03 by vbastion         ###   ########.fr       */
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

void	init_token_table(t_kvp *tok)
{
	tok[0] = (t_kvp){.key=(void *)NEWLINE, .val=(char *)"NEWLINE", .typ=INT_STR};
	tok[1] = (t_kvp){.key=(void *)SEMICOL, .val=(char *)"SEMICOL", .typ=INT_STR};
	tok[2] = (t_kvp){.key=(void *)IO_NUMBER, .val=(char *)"IO_NUMBER", .typ=INT_STR};
	tok[3] = (t_kvp){.key=(void *)WORD, .val=(char *)"WORD", .typ=INT_STR};
	tok[4] = (t_kvp){.key=(void *)ASSIGNMENT_WORD, .val=(char *)"ASSIGNMENT_WORD", .typ=INT_STR};
	tok[5] = (t_kvp){.key=(void *)OR, .val=(char *)"OR", .typ=INT_STR};
	tok[6] = (t_kvp){.key=(void *)AND, .val=(char *)"AND", .typ=INT_STR};
	tok[7] = (t_kvp){.key=(void *)LESS, .val=(char *)"LESS", .typ=INT_STR};
	tok[8] = (t_kvp){.key=(void *)GREAT, .val=(char *)"GREAT", .typ=INT_STR};
	tok[9] = (t_kvp){.key=(void *)OR_IF, .val=(char *)"OR_IF", .typ=INT_STR};
	tok[10] =(t_kvp){.key=(void *)AND_IF, .val=(char *)"AND_IF", .typ=INT_STR};
	tok[11] =(t_kvp){.key=(void *)DLESS, .val=(char *)"DLESS", .typ=INT_STR};
	tok[12] =(t_kvp){.key=(void *)DGREAT, .val=(char *)"DGREAT", .typ=INT_STR};
	tok[13] =(t_kvp){.key=(void *)LESSAND, .val=(char *)"LESSAND", .typ=INT_STR};
	tok[14] =(t_kvp){.key=(void *)GREATAND, .val=(char *)"GREATAND", .typ=INT_STR};
	tok[15] =(t_kvp){.key=(void *)TLESS, .val=(char *)"TLESS", .typ=INT_STR};
	tok[16] =(t_kvp){.key=(void *)ANDGREAT, .val=(char *)"ANDGREAT", .typ=INT_STR};
	tok[17] =(t_kvp){.key=(void *)ANDDGREAT, .val=(char *)"ANDDGREAT", .typ=INT_STR};
	tok[18] =(t_kvp){.key=(void *)DOLLAR, .val=(char *)"DOLLAR", .typ=INT_STR};
	tok[19] =(t_kvp){.key=(void *)BANG, .val=(char *)"BANG", .typ=INT_STR};
	tok[20] =(t_kvp){.key=(void *)PARAM_EXP, .val=(char *)"PARAM_EXP", .typ=INT_STR};
	tok[21] =(t_kvp){.key=(void *)CMD_SUB, .val=(char *)"CMD_SUB", .typ=INT_STR};
	tok[22] =(t_kvp){.key=(void *)ARI_EXP, .val=(char *)"ARI_EXP", .typ=INT_STR};
	tok[23] =(t_kvp){.key=(void *)COMMENT, .val=(char *)"COMMENT", .typ=INT_STR};
	tok[24] =(t_kvp){.key=(void *)0, .val=NULL, .typ=INT_STR};
}

void	print_toklist(t_token *toklist)
{
	t_kvp	tok[25];
	int			i;

	init_token_table(tok);
	while (toklist)
	{
		dump_token(toklist);
		ft_putstr(" Type: ");
		i = 0;
		while ((unsigned long)tok[i].key != toklist->type && tok[i].key)
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
	t_kvp	tok[25];
	t_token		*ret;
	int			i;

	if ((ret = filter_tokens(*toklist)) != SUCCESS)
	{
		i = 0;
		init_token_table(tok);
		while ((unsigned long)tok[i].key != ret->type && tok[i].key)
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
