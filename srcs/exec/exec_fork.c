/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 14:46:43 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/23 11:47:15 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

/*
**	DO_DUP:	Duplicates fd at value given by the `tar` argument
**	DO_CLO: Closes the fd given;
**	DO_NUL:	Set the fd value to -1, indicating nothing needs to be done further
**	DO_MOV:	Changes fd position to another int pointed by `move`
*/

#define DO_DUP 1
#define DO_CLO 2
#define DO_NUL 4
#define DO_MOV 8

static void				transform_fd(int *fd, int flag, int tar, int *move)
{
	if (*fd != -1)
	{
		if (flag & DO_MOV)
			*move = *fd;
		if (flag & DO_DUP)
			dup2(*fd, tar);
		if (flag & DO_CLO)
			close(*fd);
		if (flag & DO_NUL)
			*fd = -1;
	}
}

static void				fork_child(t_proc *p, int *pipes, pid_t pgid)
{
	if (p->next == NULL)
	{
		transform_fd(pipes + 2, DO_DUP | DO_CLO, STDIN_FILENO, NULL);
		transform_fd(pipes + 3, DO_CLO, 0, NULL);
		transform_fd(pipes, DO_CLO, 0, NULL);
		transform_fd(pipes + 1, DO_CLO, 0, NULL);
	}
	else
	{
		transform_fd(pipes + 1, DO_DUP | DO_CLO, STDOUT_FILENO, NULL);
		transform_fd(pipes, DO_CLO, 0, NULL);
		transform_fd(pipes + 2, DO_DUP | DO_CLO, STDIN_FILENO, NULL);
		transform_fd(pipes + 3, DO_CLO, 0, NULL);
	}
	if (job_setpgid(getpid(), pgid) == -1)
		exit(1);
	if (p->status & JOB_CMP)
		exit(1);
	else
		proc_exec(p);
}

int						fork_do(t_proc *p, pid_t pgid, int *pipes)
{
	pid_t				pid;

	if ((pid = fork()) == 0)
		fork_child(p, pipes, pgid);
	else if (pid < 0)
		return (print_err("42sh: fork: could not fork\n", -1));
	else
	{
		transform_fd(pipes + 2, DO_CLO | DO_NUL, 0, NULL);
		transform_fd(pipes + 3, DO_CLO | DO_NUL, 0, NULL);
		transform_fd(pipes + 1, DO_CLO | DO_NUL, 0, NULL);
		transform_fd(pipes, DO_MOV, 0, pipes + 2);
		p->pid = pid;
		if (job_setpgid(pid, pgid) == -1)
			return (-1);
		return (pid);
	}
	return (0);
}
