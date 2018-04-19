/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_getnextexec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 10:33:31 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/19 10:33:33 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

t_job					*job_getnextexec(t_job *j)
{
	int					status;

	status = j->status & 0xFF;
	j = j->next;
	while (j != NULL)
	{
		if (status && j->type == JOB_ERR)
			return (j);
		else if (status == 0 && j->type == JOB_OK)
			return (j);
		j = j->next;
	}
	return (NULL);
}
