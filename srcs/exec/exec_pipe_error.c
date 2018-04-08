/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 17:36:57 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/08 17:42:56 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void						clear_pipe(t_job *j, t_proc *last, int fd)
{
	t_proc					*p;
	int						status;
	int						ffd;

	ffd = -1;
	p = j->procs;
	while (p != last)
	{
		kill(p->pid, SIGKILL);
		waitpid(p->pid, &status, WUNTRACED);
		p = p->next;
	}
	while (p != NULL)
	{
		write(fd, (char *)&ffd, sizeof(int));
		p = p->next;
	}
}
