/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 17:25:27 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/05 17:22:54 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h> //
# include <sys/types.h>
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>

# include "token.h"
# include "ft_mem.h"
# include "ft_string.h"
# include "environ.h"
# include "qbuf.h"

# define EXE_LCHD ("launched")

# define FTSH_RUN 0
# define FTSH_SIG 1
# define FTSH_EXI 2

typedef struct s_proc	t_proc;
typedef struct s_job	t_job;

struct					s_proc
{
	struct s_proc		*next;
	char				**argv;
	pid_t				pid;
	char				**env;
	char				completed;
	char				stopped;
	int					status;
	t_redir				*redirs;
//	int					std[3];
//	int					*other;
};

struct					s_job
{
	char				*command;
	t_proc				*procs;
	pid_t				pgid;
	char				notified;
	struct termios		tmodes;
	int					stdin;
	int					stdout;
	int					stderr;
};

t_proc					*proc_new(char **argv);
void					proc_insert(t_proc **head, t_proc **curr, t_proc *p);
void					proc_clear(t_proc **proc);

void					proc_exec(t_proc *p, pid_t pgid, int fd[3], int fg,
									t_env *env);
int						proc_chgstat(t_job *job, pid_t pid, int status);

t_job					*job_new(char *cmd, t_proc *plist);
void					job_insert(t_job **head, t_job **curr, t_job *j);
void					job_clear(t_job **jobs);

t_job					*job_find(pid_t pid, t_job *job_list);
int						job_stopped(t_job *job);
int						job_completed(t_job *job);

int						job_exec(t_job *j, int fg, t_env *env);

void					job_wait(t_job *j);
void					job_putbg(t_job *j, int cont);
void					job_putfg(t_job *j, int cont, t_env *env);

void					job_fmtinfo(t_job *j, char *status);

void					setup_signals(void (*sig)()); 

#endif
