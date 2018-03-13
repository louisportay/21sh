/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_restore.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 11:17:11 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/13 11:23:31 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void			proc_restore(t_proc *p)
{
	p->stopped = 0;
}

void				jc_restore(t_job *j)
{
	j->stopped = 0;
	if (j->parent != j)
		j->parent->stopped = 0;
	proc_foreach(j->procs, &proc_restore);
	kill(-j->pgid, SIGCONT);
}
