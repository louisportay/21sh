/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_lifecycle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:03:23 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/18 19:51:25 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

t_job					*job_new(int type)
{
	t_job				*job;

	if (type != JOB_OK && type != JOB_ERR && type != JOB_HEAD)
		return (NULL);
	if ((job = (t_job *)ft_pmemalloc(sizeof(t_job), &on_emem, NOMEM)) == NULL)
		return (NULL);
	job->parent = job;
	job->type = type;
	return (job);
}

void					job_insert(t_job **head, t_job **curr, t_job *j)
{
	if (*head == NULL)
		*head = j;
	else
		(*curr)->next = j;
	*curr = j;
}

char					*job_last_argv(t_job *j)
{
	t_proc				*p;
	size_t				i;

	if (j->procs == NULL)
		return (NULL);
	p = j->procs;
	while (p->next != NULL)
		p = p->next;
	i = 0;
	if (p->argv[i] == NULL)
		return (NULL);
	while (p->argv[i + 1] != NULL)
		i++;
	return (ft_strdup(p->argv[i]));
}
