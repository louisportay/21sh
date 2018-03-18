/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 09:42:08 by lportay           #+#    #+#             */
/*   Updated: 2018/03/18 19:36:34 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	err_tok(t_token **toklist, t_token *bad_tok)
{
	t_kvp	tok[20];
	int			i;

	i = 0;
	init_token_table(tok);
	while ((unsigned long)tok[i].key != bad_tok->type && tok[i].key)
			i++;
	dprintf(STDERR_FILENO, "-LEXER- 21sh: syntax error near unexpected token `%s'\n", (char *)tok[i].val);
	clear_following_redirs(bad_tok);
	delete_toklist(toklist);
}

void	init_tokenizer(t_dlist **line, t_token **tlist,
		t_token **ltok, t_stack **qstate)
{
	*qstate = NULL;
	stack_push(qstate, stack_create(UNQUOTED));
	*tlist = new_token(*line);
	(*tlist)->last_letter = *line;
	(*tlist)->type = HEAD;
	*ltok = *tlist;
//	*line = (*line)->next;
}

/*
** if (toklist)
**	print_toklist(toklist->next);
*/

//lui faire retourner une toklist avec la ligne + les tokens associés
t_toklist		tokenizer(t_dlist *line)
{
	t_token *toklist;
	t_token *last_tok;
	t_stack *quoting;
	t_dlist *split_line;

	
	if (!line)
		wrap_exit(EXIT_SUCCESS, get_ctxaddr());
	init_tokenizer(&line, &toklist, &last_tok, &quoting);

	split_line = line->next;
	
	while (split_line)
	{
		tokrules(last_tok, split_line, &quoting);
		if (!split_line->next)
			line = split_line;
		split_line = split_line->next;
		if (last_tok->next)
			last_tok = last_tok->next;
	}
	split_line = line;
	if (quoting->state & (BSLASH | SQUOTE | DQUOTE))
	{
		write(STDOUT_FILENO, "\n", 1); 
		ft_readline(get_ctxaddr(), &get_ctxaddr()->line, PS2);
		if (!get_ctxaddr()->line.line)
		{
			ft_dlsthead(&split_line);
			ft_dlstdel(&split_line, &delvoid);
			delete_toklist(&toklist);
			if (!(quoting->state & BSLASH))
			{
				write(STDIN_FILENO, "\n", 1);
				stack_del(&quoting);
				dump_err(BADQUOTES);
			}
			else
			{
				stack_del(&quoting);
				wrap_exit(EXIT_SUCCESS, get_ctxaddr());
			}
			return (NULL);
		}
		join_lines(&get_ctxaddr()->line.line, &split_line);
	}
		
	
	//si la stack est pas vide -->get une nouvelle ligne
	//si elle est NULL --> err_quote
	//sinon join_lines

	if ((last_tok = filter_tokens(toklist)))
		err_tok(&toklist, last_tok);
	stack_del(&quoting);
	write(STDOUT_FILENO, "\n", 1); 
	return (toklist);
}
