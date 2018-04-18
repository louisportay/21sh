/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 12:56:32 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/18 20:06:26 by vbastion         ###   ########.fr       */
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

static int				validate(struct s_token *tokens)
{
	if (tokens->type == NEWLINE)
	{
		if (tokens->next != NULL)
			fatal_err(CTX_ERR, get_ctxaddr());
		return (0);
	}
	else if ((tokens->type & (SEMICOL)) != 0)
	{
		if (tokens->next == NULL || tokens->next->type == NEWLINE)
			return (0);
		return (1);
	}
	return (-1);
}

void					*get_nextcommand(t_token **tokens)
{
	t_job				*job[3];

	job[0] = NULL;
	while ((job[2] = job_getnext(tokens, job[0])) != NULL)
		job_insert(job, job + 1, job[2]);
	return (job[0]);
}

static void				job_forward(t_job **head, t_job **curr, t_job *elem)
{
	if (*head == NULL)
		*head = elem;
	else
		(*curr)->forward = elem;
	*curr = elem;
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
		if ((job[2] = get_nextcommand(&tokens)) == NULL)
			return (job_clearall(job));
		if ((ret = validate(tokens)) == -1)
		{	/*	CRITICAL PARSING ERROR	*/	
			exit(-42);
			//	NEED BETTER ERROR HANDLING AND CLEANING
		}
		job_forward(job, job + 1, job[2]);
		if (ret == 0)
			break ;
	}
	return (job[0]);
}
