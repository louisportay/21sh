/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:06:04 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/14 16:31:13 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void					job_wait(t_job *j)
{
	int					status;
	pid_t				pid;

//	t_proc				*p;
//
//	p = j->procs;
//	while (p != NULL)
//	{
//		dprintf(STDERR_FILENO, "Waiting for \033[33m%d\033[0m\n", p->pid);
//		pid = waitpid(p->pid, &status, WUNTRACED);
//		if (pid == -1)
//		{
//			perror("waitpid");
//			return ;
//		}
//		else
//		{
//			printf("\033[32m%d\033[0m is done\n", pid);
//			p = p->next;
//		}
//	}
//	printf("\033[56mIn wait\033[0m\n");
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

void					job_putfg(t_job *j, int continued, t_ctx *ctx)
{
	int ret;
	for (t_proc *p = j->procs; p != NULL; p = p->next)
		printf("pgid: %d - pid: %d - real pgid: %d\n", j->pgid, p->pid, getpgid(p->pid));
	printf("\033[56mIn foreground\033[0m\n");
	if ((ret = tcsetpgrp(ctx->fd, j->pgid)) != 0)
		perror("tcsetpgrp");
	if ((ret = tcsetattr(ctx->fd, TCSADRAIN, &ctx->oldtios)) != 0)
		perror("tcsetattr");
	(void)continued;
//	if (continued != 0)
//	{
//		if ((ret = tcsetattr(ctx->fd, TCSADRAIN, &j->tmodes)) != 0)
//			perror("tcsetattr");
//		if (kill(-j->pgid, SIGCONT) < 0)
//			ft_putstr_fd("Kill error on kill zombies", STDERR_FILENO);
//	}
	job_wait(j);
	if ((ret = tcsetattr(ctx->fd, TCSADRAIN, &ctx->tios)) != 0)
		perror("tcsetattr reset");
	if ((ret = tcsetpgrp(ctx->fd, ctx->pgid)) != 0)
		perror("tcsetpgrp");
//	if ((ret = tcgetattr(ctx->fd, &j->tmodes)) != 0)
//		perror("tcgetattr");
//	if ((ret = tcsetattr(ctx->fd, TCSADRAIN, &ctx->tios)) != 0)
//		perror("tcsetattr");
}
