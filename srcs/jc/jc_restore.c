/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_restore.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 11:17:11 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/14 17:06:28 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void			proc_restore(t_proc *p)
{
	p->status &= ~JOB_STP;
}

void				jc_restore(t_job *j)
{
	j->status &= ~JOB_STP;
	if (j->parent != j)
		j->parent->status &= ~JOB_STP;
	proc_foreach(j->procs, &proc_restore);
	kill(-j->pgid, SIGCONT);
}
