/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_lifecycle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 15:03:23 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/24 17:26:54 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_job					*job_new(char *cmd, t_proc *plist)
{
	t_job				*job;

	if ((job = (t_job *)ft_memalloc(sizeof(t_job))) == NULL)
		return (NULL);
	job->first_process = plist;
	job->command = cmd;
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
