/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 09:42:08 by lportay           #+#    #+#             */
/*   Updated: 2018/04/16 18:14:13 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void	err_tok(t_token **toklist, t_token *bad_tok)
{
	t_kvp	tok[20];
	int		i;

	i = 0;
	init_token_table(tok);
	while ((unsigned long)tok[i].key != bad_tok->type && tok[i].key)
		i++;
	ft_dprintf(STDERR_FILENO,
			"42sh: syntax error near unexpected token `%s'\n",
			(char *)tok[i].val);
	clear_following_redirs(bad_tok);
	delete_toklist(toklist);
}

void	init_tokenizer(t_dlist **line, t_token **tlist,
		t_token **ltok, t_stack **qstate)
{
	*qstate = NULL;
	if (stack_create_push(qstate, UNQUOTED) == -1)
		fatal_err(NOMEM, get_ctxaddr());
	if ((*tlist = new_token(*line)) == NULL)
		fatal_err(NOMEM, get_ctxaddr());
	(*tlist)->last_letter = *line;
	(*tlist)->type = HEAD;
	*ltok = *tlist;
	*line = (*line)->next;
}

/*
** if (toklist)
**	print_toklist(toklist->next);
*/

t_token	*tokenizer(t_dlist *line)
{
	t_token *toklist;
	t_token *last_tok;
	t_stack *quote_state;

	init_tokenizer(&line, &toklist, &last_tok, &quote_state);
	while (line)
	{
		tokrules(last_tok, line, &quote_state);
		line = line->next;
		if (last_tok->next)
			last_tok = last_tok->next;
	}
	if ((last_tok = filter_tokens(toklist)))
		err_tok(&toklist, last_tok);
	stack_del(&quote_state);
	return (toklist);
}
