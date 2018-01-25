#include "exec.h"

void					exit_err(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(1);
}

void					setup_fd(int lhs, int rhs)
{
	if (lhs != rhs)
	{
		dup2(lhs, rhs);
		close(lhs);
	}
}

void					setup_signals(void (*sig)())
{
	signal(SIGINT, 	sig);
	signal(SIGTSTP, sig);
	signal(SIGQUIT, sig);
	signal(SIGTTOU, sig);
	signal(SIGTTIN, sig);
	signal(SIGCHLD, sig);
}

void					*PH_GET_BUILTIN(char *name)
{
	(void)name;
	return (NULL);
}

void					proc_exec(t_proc *p, pid_t pgid, int fd[3], int fg,
									t_env *env)
{
	char				*path;
	int					(*builtin)();
	char				**astrenv;

	(void)pgid;
	(void)fg;
	builtin = PH_GET_BUILTIN(p->argv[0]);
	if (builtin == NULL && get_path(p->argv[0], env, &path) == -1)
	{
		printf("%s: %s: %s\n", "21sh", p->argv[0], "Command not found");
		exit(1);
	}
	if (env->istty)
		setup_signals(SIG_DFL);
	setup_fd(fd[0], STDIN_FILENO);
	setup_fd(fd[1], STDOUT_FILENO);
	setup_fd(fd[2], STDERR_FILENO);
	if (builtin != NULL)
		exit(builtin(p->argv, env));
	if ((astrenv = ft_env_toastr(env->env)) == NULL)
		exit_err("Not enough memory\n"); // BIG BIG ERROR BUT MIGHT BE UNESCAPBLE
	execve(path, p->argv, astrenv);
	exit_err("Could not exec...\n");
}
