/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 12:56:32 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/12 12:44:52 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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
		if (t->next == NULL || token_issep(t->next))
		{
			token_dumperror(t);
			proc_clear(p);
			return (NULL);
		}
		t = t->next;
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
	t_ptok				*pt[3];

	t = *toks;
	pt[0] = NULL;
	while (t->type == AND_IF)
	{
		t = t->next;
		if ((p = get_pipe(&t)) == NULL)
			return (ptok_clear(pt));
		pt[2] = (t_ptok *)ft_pmemalloc(sizeof(t_ptok), &on_emem, NOMEM);
		pt[2]->job = (t_job *)ft_pmemalloc(sizeof(t_job), &on_emem, NOMEM);
		pt[2]->job->procs = p;
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
	if ((ptok->job->procs = get_pipe(&tokz)) == NULL)
		return (ptok_clear(&ptok));
	if (tokz->type == AND_IF && (ptok->ok = get_ands(&tokz)) == NULL)
		return (ptok_clear(&ptok));
	if (tokz->type == OR_IF)
	{
		if ((ptok->err = ptok_next(&tokz)) == NULL)
			return (ptok_clear(&ptok));
	}
	*tokens = tokz;
	return (ptok);
}

t_ptok					*parse(struct s_token *tokens)
{
	t_ptok				*ret;

	if ((ret = ptok_next(&tokens)) == NULL)
		return (NULL);
	return (ret);
}
