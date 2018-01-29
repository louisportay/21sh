/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 13:45:11 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/24 17:29:41 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	#include "exec.h"
#include "environ.h"
#include "exec.h"

#define CMD ("ls -l | cat -e")

#include <stdio.h>
#include <term.h>
#include <sys/syslimits.h>
#include <termios.h>

extern char	**environ;

int			main(int ac, char **av)
{
	t_env	env;
	char	*path;
	t_proc	*proc[3];
	t_job	*job;
	char	*cmd;
	char	**argv;

	if (ac < 2)
		return (1);
	env_setup(&env, environ);
	char *term = getenv("TERM");
	tgetent(0, term);
	tcgetattr(STDIN_FILENO, &env.told);
	ft_memcpy(&env.tnew, &env.told, sizeof(struct termios));
	cmd = NULL;
	proc[0] = NULL;
	for (int i = 1; i  < ac; i++)
	{
		argv = ft_strsplit(av[i], ' ');
		for (int a = 0; argv[a] != NULL; a++)
			printf("av[%d]: %s%s", a, argv[a], argv[a + 1] == NULL ? "\n" : " - ");
		if (get_path(argv[0], &env, &path))
		{
			if ((proc[2] = proc_new(argv)) == NULL)
				fprintf(stderr, "malloc error\n");
			else
				proc_insert(proc, proc + 1, proc[2]);
			if (cmd == NULL)
				cmd = ft_strdup(argv[0]);
			else
				ft_strjoinc(cmd, argv[0], '|');
		}
		else
			printf("21sh: %s: command not found\n", av[1]);
	}
	printf("cmd: %s\n", cmd);
	job = job_new(cmd, proc[0]);
	job_exec(job, 1, &env);
//	if (get_path(av[1], &env, &path))
//	{
//		printf("Path: %s\n", path);
//		t_proc *proc;
//		proc = proc_new(av + 1);
//		proc_exec(proc, 0, (int[]){0, 1, 2}, 1, &env);
//	}
//	else
//		printf("21sh: %s: command not found\n", av[1]);
	return (0);
}
//	int main(int ac, char **av)
//	{
//		t_job	*j;
//		t_proc	*p[3];
//	
//		(void)ac;
//		(void)av;
//		if ((j = (t_job *)ft_memalloc(sizeof(t_job))) == NULL)
//			return (1);
//		p[0] = NULL;
//		p[2] = proc_new((char *[]){"/bin/ls", "-l", NULL});
//		proc_insert(p, p + 1, p[2]);
//		p[2] = proc_new((char *[]){"/bin/cat", "-e", NULL});
//		proc_insert(p, p + 1, p[2]);
//		j = job_new(ft_strdup(CMD), p[0]);
//		job_exec(j, 1, 1);
//		return (0);
//	}
