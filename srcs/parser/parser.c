/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 12:56:32 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/19 10:23:05 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

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

static void				job_forward(t_job **head, t_job **curr, t_job *elem)
{
	if (*head == NULL)
		*head = elem;
	else
		(*curr)->forward = elem;
	*curr = elem;
}

/*
**	If it returns NULL, maybe add error printing.
*/

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
			return (job_clearall(job));
		job_forward(job, job + 1, job[2]);
		if (ret == 0)
			break ;
	}
	return (job[0]);
}
