/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 12:56:32 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/11 20:10:45 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

#define FMT_SYN ("21sh: syntax error near unexpected token %s\n")
#define FMT_EOF ("EOF")
#define FMT_AND ("&")
#define FMT_SEM (";")
#define FMT_COM ("#")
#define FMT_OR ("|")
#define FMT_ORI ("||")
#define FMT_ANI ("&&")

int						token_issep(t_token *tok)
{
	return ((tok->type & (NEWLINE | AND | SEMICOL | COMMENT | OR | OR_IF
							| AND_IF)) != 0);
}

void					*token_dumperror(t_token *tok)
{
	if (tok == NULL || tok->type == NEWLINE)
		dprintf(STDERR_FILENO, FMT_SYN, FMT_EOF);
	else if (tok->type == AND)
		dprintf(STDERR_FILENO, FMT_SYN, FMT_AND);
	else if (tok->type == SEMICOL)
		dprintf(STDERR_FILENO, FMT_SYN, FMT_SEM);
	else if (tok->type == COMMENT)
		dprintf(STDERR_FILENO, FMT_SYN, FMT_COM);
	else if (tok->type == OR)
		dprintf(STDERR_FILENO, FMT_SYN, FMT_OR);
	else if (tok->type == OR_IF)
		dprintf(STDERR_FILENO, FMT_SYN, FMT_ORI);
	else if (tok->type == AND_IF)
		dprintf(STDERR_FILENO, FMT_SYN, FMT_ANI);
	return (NULL);
}

void					assert_next_token(t_token *tok)
{
	if (tok->type == NEWLINE)
		ft_putstr("NEWLINE: end of parse\n");
	else if (tok->type == AND)
		ft_putstr("AND: Background job\n");
	else if (tok->type == SEMICOL)
		ft_putstr("SEMICOL: Need a proc after, else parse error\n");
	else if (tok->type == COMMENT)
		ft_putstr("COMMENT: end of parse\n");
	else if (tok->type == OR)
		ft_putstr("OR: pipeline\n");
	else if (tok->type == OR_IF)
		ft_putstr("OR_IF: Conditional execution of next\n");
	else if (tok->type == AND_IF)
		ft_putstr("AND_IF: Conditional execution of next\n");
}

void					proc_insert(t_proc **head, t_proc **curr, t_proc *e)
{
	if (*head == NULL)
		*head = e;
	else
		(*curr)->next = e;
	*curr = e;
}

t_proc					*get_pipe(t_token **tokz)
{
	t_proc				*p[3];
	t_token				*t;

	t = *tokz;
	p[2] = proc_next(&t);
	p[0] = NULL;
	proc_insert(p, p + 1, p[2]);
	while (t->type == OR)
	{
		if (token_issep(t))
		{
			token_dumperror(t);
			proc_clear(p);
			return (NULL);
		}
		p[2] = proc_next(&t);
		proc_insert(p, p + 1, p[2]);
	}
	*tokz = t;
	return (p[0]);
}

t_ptok					*get_ands(t_token **toks)
{
	t_token				*t;
	t_proc				*p;
	t_job				*j;
	t_ptok				*pt[3];

	t = *toks;
	pt[0] = NULL;
	while (t->type == AND_IF)
	{
		t = t->next;
		if ((p = get_pipe(&t)) == NULL)
		{
			ptok_clear(pt);
			return (NULL);
		}
		pt[2] = (t_ptok *)ft_pmemalloc(sizeof(t_ptok), &on_emem, NOMEM);
		j = (t_job *)ft_pmemalloc(sizeof(t_job), &on_emem, NOMEM);
		j->procs = p;
		ptok_insert(pt, pt + 1, pt[2]);
	}
	*toks = t;
	return (pt[0]);
}

t_ptok					*ptok_next(t_token **tokens)
{
	t_token				*tokz;
	t_ptok				*ptok;

	if (*tokens == NULL || token_issep(tokz = (*tokens)->next))
		return (token_dumperror(*tokens == NULL ? NULL : tokz));
	ptok = (t_ptok *)ft_pmemalloc(sizeof(t_ptok), &on_emem, NOMEM);
	ptok->job = (t_job *)ft_pmemalloc(sizeof(t_job), &on_emem, NOMEM);
	if ((ptok->job->procs = get_pipe(&tokz)) == NULL
		|| (ptok->ok = get_ands(&tokz)) == NULL)
	{
		ptok_clear(&ptok);
		return (NULL);
	}
	if ((*tokens)->type == OR_IF
		&& (ptok->err = ptok_next(tokens)) == NULL)
	{
		ptok_clear(&ptok);
		return (NULL);
	}
	*tokens = tokz;
	return (ptok);
}

t_ptok					*parse(struct s_token *tokens)
{
	t_ptok				*ret;

	if ((ret = ptok_next(&tokens)) == NULL)
		return (NULL);
	assert_next_token(tokens);
	return (NULL);// Later when working I will return sth else
}
