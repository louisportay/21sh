/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:06:04 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/12 20:57:02 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void					job_wait(t_job *j)
{
	int					status;
	pid_t				pid;

	printf("\033[56mIn wait\033[0m\n");
	while (1)
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
		printf("done (\033[31m%d\033[0m)\n", pid);
		if (pid == -1)
		{
			perror("waitpid");
			return ;
		}
		if (proc_chgstat(j, pid, status)
			|| job_stopped(j)
			|| job_completed(j))
			break ;
	}
}

void					job_putbg(t_job *j, int continued)
{
	printf("\033[56mIn background\033[0m\n");
	if (continued != 0)
	{
		if (kill(-j->pgid, SIGCONT) < 0)
			ft_putstr_fd("Kill error on kill zombies", STDERR_FILENO);
	}
}

void					job_putfg(t_job *j, int continued, t_ctx *env)
{
	int ret;
	printf("\033[56mIn foreground\033[0m\n");
	if ((ret = tcsetpgrp(env->fd, j->pgid)) != 0)
		perror("tcsetpgrp");
	if (continued != 0)
	{
		if ((ret = tcsetattr(env->fd, TCSADRAIN, &j->tmodes)) != 0)
			perror("tcsetattr");
		if (kill(-j->pgid, SIGCONT) < 0)
			ft_putstr_fd("Kill error on kill zombies", STDERR_FILENO);
	}
	job_wait(j);
	if ((ret = tcsetpgrp(env->fd, env->pgid)) != 0)
		perror("tcsetpgrp");
	if ((ret = tcgetattr(env->fd, &j->tmodes)) != 0)
		perror("tcgetattr");
	if ((ret = tcsetattr(env->fd, TCSADRAIN, &env->tios)) != 0)
		perror("tcsetattr");
}
