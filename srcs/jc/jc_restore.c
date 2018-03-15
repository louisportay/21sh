/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_restore.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 11:17:11 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/15 16:32:03 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static char			*get_cmd(t_proc *p)
{
	t_qbuf			*buf;
	int				i;

	buf = qbuf_new(1 << 8);
	i = 0;
	while (p->argv[i] != NULL)
	{
		qbuf_add(buf, p->argv[i]);
		i++;
		if (p->argv[i] != NULL)
			qbuf_addc(buf, ' ');
	}
	return (qbuf_del(&buf));
}

static void			proc_restore(t_proc *p, void *data)
{
	t_proc			*caller;
	char			*cmd;
	char			*str;
	t_list			**curr;
	t_list			*l;

	if ((p->status & JOB_SIG) && (p->status & 0xFF) != SIGINT)
	{
		caller = (t_proc *)(((void **)data)[0]);
		curr = (t_list **)(((void **)data)[1]);
		cmd = get_cmd(p);
		asprintf(&str, "%d signaled: %d | %s\n", p->pid, p->status & 0xFF, cmd);
		l = list_create(cmd);
		ft_assert((void **[]){(void **)&str, (void **)&cmd, (void **)l}, 3);
		ft_list_insert(&caller->data.out, curr, l);
		ft_strdel(&str);
	}
	p->status &= ~JOB_STP;
}

void				jc_restore(t_job *j, t_proc *caller, t_list **curr)
{
	j->status &= ~JOB_STP;
	if (j->parent != j)
		j->parent->status &= ~JOB_STP;
	proc_foreach_data(j->procs, &proc_restore,
						(void *)((void *[]){(void *)caller, (void *)curr}));
	kill(-j->pgid, SIGCONT);
}
