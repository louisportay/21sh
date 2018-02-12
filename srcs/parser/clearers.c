/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clearers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 19:49:00 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/12 10:24:57 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				proc_clear(t_proc **proc)
{
	if ((*proc)->next != NULL)
		proc_clear(&(*proc)->next);
	if ((*proc)->argv != NULL)
		ft_astr_clear(&(*proc)->argv);
	if ((*proc)->env != NULL)
		ft_astr_clear(&(*proc)->env);
	if ((*proc)->asmts != NULL)
		asmt_clear(&(*proc)->asmts);
	ft_memdel((void **)proc);
}

void				asmt_clear(t_asmt **asmt)
{
	if ((*asmt)->next != NULL)
		asmt_clear(&(*asmt)->next);
	ft_strdel(&(*asmt)->key);
	ft_strdel(&(*asmt)->value);
	ft_memdel((void **)asmt);
}

void				*ptok_clear(t_ptok **ptok)
{
	if ((*ptok)->job != NULL)
		job_clear(&(*ptok)->job);
	if ((*ptok)->ok != NULL)
		ptok_clear(&(*ptok)->ok);
	if ((*ptok)->err != NULL)
		ptok_clear(&(*ptok)->err);
	if ((*ptok)->next != NULL)
		ptok_clear(&(*ptok)->next);
	ft_memdel((void **)ptok);
	return (NULL);
}

void				job_clear(t_job **job)
{
	t_job			*j;

	j = *job;
	if (j->command != NULL)
		ft_strdel(&j->command);
	if (j->procs != NULL)
		proc_clear(&j->procs);
	ft_memdel((void **)job);
}
