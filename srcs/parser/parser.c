/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 12:56:32 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/11 13:44:59 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static t_proc			*get_pipe(t_token **tokz)
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

static t_job			*get_ands(t_token **toks, t_job *parent)
{
	t_token				*t;
	t_proc				*p;
	t_job				*j[3];

	t = *toks;
	j[0] = NULL;
	j[1] = NULL;
	while (t->type == AND_IF)
	{
		t = t->next;
		if ((p = get_pipe(&t)) == NULL)
			return (job_safeclear(j));
		j[2] = job_new(p);
		j[2]->parent = parent;
		if (j[1] != NULL)
			j[1]->ok = j[2];
		if (j[0] == NULL)
			j[0] = j[2];
		j[1] = j[2];
	}
	*toks = t;
	return (j[0]);
}

static t_job			*job_getnext(t_token **tokens, t_job *parent)
{
	t_token				*tokz;
	t_job				*job;

	if (*tokens == NULL || token_issep(tokz = (*tokens)->next))
		return (token_dumperror(*tokens == NULL ? NULL : tokz));
	job = job_new(NULL);
	job->parent = (parent == NULL) ? job : parent;
	if ((job->procs = get_pipe(&tokz)) == NULL)
		return (job_safeclear(&job));
	if (tokz->type == AND_IF
		&& (job->ok = get_ands(&tokz, parent == NULL ? job : parent)) == NULL)
		return (job_safeclear(&job));
	if (tokz->type == OR_IF)
	{
		if ((job->err = job_getnext(&tokz, parent)) == NULL)
			return (job_safeclear(&job));
	}
	job_updateands(job);
	*tokens = tokz;
	return (job);
}

static int				handle(struct s_token *tokens, t_job *job[3])
{
	if (tokens->type == NEWLINE)
	{
		if (tokens->next != NULL)
			fatal_err(CTX_ERR, get_ctxaddr());
		job_insert(job, job + 1, job[2]);
		return (0);
	}
	else if ((tokens->type & (SEMICOL)) != 0)
	{
		job_insert(job, job + 1, job[2]);
		if (tokens->next == NULL || tokens->next->type == NEWLINE)
			return (0);
		return (1);
	}
	return (-1);
}

t_job					*parse(struct s_token *tokens)
{
	t_job				*job[3];
	int					ret;

	job[0] = NULL;
	if (tokens == NULL || tokens->type == NEWLINE
		|| (tokens->next != NULL && tokens->next->type == NEWLINE))
		return (NULL);
	while (1)
	{
		if ((job[2] = job_getnext(&tokens, NULL)) == NULL)
			return (job_safeclear(&job[0]));
		if ((ret = handle(tokens, job)) == 0)
			break ;
		else if (ret != 1)
		{
			ft_dprintf(STDERR_FILENO, "42sh: syntax error, unexpected token\n");
			return (job_safeclear(job));
		}
	}
	return (job[0]);
}
