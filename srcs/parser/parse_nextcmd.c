/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_nextcmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 10:19:50 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/19 12:10:46 by vbastion         ###   ########.fr       */
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
	proc_insert(p, p + 1, p + 2);
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
		proc_insert(p, p + 1, p + 2);
	}
	*tokz = t;
	return (p[0]);
}

static t_job			*job_getbytype(t_token *tokens)
{
	if (tokens == NULL)
		return (NULL);
	else if (tokens->type == HEAD || tokens->type == SEMICOL)
		return (job_new(JOB_HEAD));
	else if (tokens->type == AND_IF)
		return (job_new(JOB_OK));
	else if (tokens->type == OR_IF)
		return (job_new(JOB_ERR));
	return (NULL);
}

static t_job			*job_getnext(t_token **tokens, t_job *parent)
{
	t_job				*job;
	t_token				*tokz;

	if (*tokens == NULL)
		return (NULL);
	if ((job = job_getbytype(*tokens)) == NULL)
		return (NULL);
	tokz = (*tokens)->next;
	if ((job->procs = get_pipe(&tokz)) == NULL)
		return (job_safeclear(&job));
	job->parent = parent != NULL ? parent : job;
	*tokens = tokz;
	return (job);
}

struct s_job			*get_nextcommand(t_token **tokens)
{
	t_job				*job[3];

	job[0] = NULL;
	while ((job[2] = job_getnext(tokens, job[0])) != NULL)
	{
		job_insert(job, job + 1, job[2]);
		if (*tokens != NULL && (*tokens)->type == SEMICOL)
			break ;
	}
	return (job[0]);
}
