/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 12:56:32 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/11 12:26:36 by vbastion         ###   ########.fr       */
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

t_ptok					*parse(struct s_token *tokens)
{
	t_proc				*proc;
	t_proc				*cproc;
	t_token				*tokz;
	t_ptok				*ptok;

	tokz = tokens->next;
	proc = proc_next(&tokz);
	ptok = (t_ptok *)ft_pmemalloc(sizeof(t_ptok), &on_emem, NOMEM);
	ptok->job = (t_job *)ft_pmemalloc(sizeof(t_job), &on_emem, NOMEM);
	proc_insert(&ptok->job->procs, &cproc, proc);
	while (tokz->type == OR)
	{
		tokz = tokz->next;
		proc = proc_next(&tokz);
		proc_insert(&ptok->job->procs, &cproc, proc);
	}
	job_print(ptok->job);
	return (NULL);// Later when working I will return sth else
}
