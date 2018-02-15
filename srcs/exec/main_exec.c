/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 13:45:11 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/12 18:58:58 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//	#include "exec.h"
#include "ft_21sh.h"

#define CMD ("ls -l | cat -e")

#include <stdio.h>
#include <term.h>
#include <sys/syslimits.h>
#include <termios.h>

extern char	**environ;

void job_print(t_job *j)
{
	t_proc	*p;
	int		i;

	printf("DEBUGGING PROCESSES CREATED:\n");
	p = j->procs;
	while (p != NULL)
	{
		i = 0;
		printf("addr of proc argv: %p: ", p->argv);
		while (p->argv[i] != NULL)
		{
			printf("%s%s", p->argv[i], p->argv[i + 1] != NULL ? " - " : "\n");
			i++;
		}
		p = p->next;
	}
	printf("END OF DEBUGGING\n");
}

int			main(int ac, char **av)
{
	t_ctx	ctx;
	t_proc	*proc[3];
	t_job	*job;
	char	*cmd;
	char	**argv;

	if (ac < 2)
		return (1);
	char *term = getenv("TERM");
	tgetent(0, term);
	tcgetattr(STDIN_FILENO, &ctx.oldtios);
	ft_memcpy(&ctx.tios, &ctx.oldtios, sizeof(struct termios));
	cmd = NULL;
	proc[0] = NULL;
	for (int i = 1; i  < ac; i++)
	{
		argv = ft_strsplit(av[i], ' ');
		//		for (int a = 0; argv[a] != NULL; a++)
		//			printf("av[%d]: %s%s", a, argv[a], argv[a + 1] == NULL ? "\n" : " - ");
		if ((proc[2] = proc_new(argv)) == NULL)
			fprintf(stderr, "malloc error\n");
		else
			proc_insert(proc, proc + 1, proc[2]);
		argv = NULL;
	}
	job = job_new(proc[0]);
	job->command = cmd;
	ctx.environ = ft_astr_dup(environ);
	ctx.istty = isatty(ctx.fd);
	if (ctx.istty)
	{
		/* Loop until we are in the foreground.  */
		while (tcgetpgrp (ctx.fd) != (ctx.pid = getpgrp ()))
			kill (- ctx.pgid, SIGTTIN);
	
		/* Ignore interactive and job-control signals.  */
		signal (SIGINT, SIG_IGN);
		signal (SIGQUIT, SIG_IGN);
		signal (SIGTSTP, SIG_IGN);
		signal (SIGTTIN, SIG_IGN);
		signal (SIGTTOU, SIG_IGN);
		signal (SIGCHLD, SIG_IGN);
	
		/* Put ourselves in our own process group.  */
		ctx.pgid = getpid ();
		if (setpgid (ctx.pgid, ctx.pgid) < 0)
		{
			perror ("Couldn't put the shell in its own process group");
			exit (1);
		}
	
		/* Grab control of the terminal.  */
		tcsetpgrp (ctx.fd, ctx.pgid);
	
		/* Save default terminal attributes for shell.  */
		tcgetattr (ctx.fd, &ctx.oldtios);
	}
	job_exec(job, 1, &ctx);
	return (0);
}
