#include "exec.h"

void					job_wait(t_job *j)
{
	int					status;
	pid_t				pid;

	while (1)
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
		if (proc_chgstat(pid, status)
			|| job_stopped(j)
			|| job_completed(j))
			break ;
	}
}

void					job_putfg(t_job *j, int continued)
{
	if (continued != 0)
	{
		if (kill(-j->pgid, SIGCONT) < 0)
			ft_putstr_fd("Kill error on kill zombies", STDERR_FILENO);
	}
}

void					job_putbg(t_env *env, t_job *j, int continued)
{
	tcsetpgrp(env->fd, j->pgid);
	if (continued != 0)
	{
		tcsetattr(env->fd, TCSADRAIN, &j->tmodes);
		if (kill(-j->pgid, SIGCONT) < 0)
			ft_putstr_fd("Kill error on kill zombies", STDERR_FILENO);
	}
	job_wait(j);
	tcsetpgrp(env->fd, env->pgid);
	tcsetattr(env->fd, &j->tmodes);
	tcsetattr(env->fd, TCSADRAIN, &env->tnew);
}
