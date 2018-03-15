/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_safeclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 16:50:47 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/07 18:36:10 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void				job_okclear(t_job **j)
{
	t_job				*j2;

	j2 = *j;
	*j = NULL;
	proc_clear(&j2->procs);
	if (j2->ok != NULL)
		job_okclear(&j2->ok);
	ft_memdel((void **)j);
}

void					job_safeclear(t_job **job)
{
	t_job				*j;

	j = (*job)->parent;
	*job = NULL;
	if (j == NULL)
		return ;
	proc_clear(&j->procs);
	if (j->ok != NULL)
		job_okclear(&j->ok);
	if (j->err != NULL)
		job_safeclear(&j->err);
	if (j->command != NULL)
		ft_strdel(&j->command);
	ft_memdel((void **)&j);
}
