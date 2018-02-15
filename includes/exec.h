/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 17:25:27 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/14 20:57:01 by vbastion         ###   ########.fr       */
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

# define EXE_LCHD ("launched")

# define FTSH_RUN 0
# define FTSH_SIG 1
# define FTSH_EXI 2

typedef struct s_asmt	t_asmt;
typedef struct s_redir	t_redir;
typedef struct s_ctx	t_ctx;

typedef struct s_proc	t_proc;
typedef struct s_job	t_job;

struct					s_proc
{
	struct s_proc		*next;
	char				**argv;
	char				**env;
	t_asmt				*asmts;
	pid_t				pid;
	char				**ctx;		// Candidate for deletion
	char				completed;
	char				stopped;
	int					status;
	t_redir				*redirs;
};

struct					s_job
{
	char				*command;
	t_proc				*procs;
	pid_t				pgid;
	char				notified;
	struct termios		tmodes;
	int					status;
	int					stdin;
	int					stdout;
	int					stderr;
};

t_proc					*proc_cr(void);
t_proc					*proc_new(char **argv);
void					proc_insert(t_proc **head, t_proc **curr, t_proc *p);
void					proc_clear(t_proc **proc);

void					proc_exec(t_proc *p, pid_t pgid, int fd[3], int fg,
									t_ctx *ctx);
int						proc_chgstat(t_job *job, pid_t pid, int status);

t_job					*job_new(t_proc *plist);
void					job_insert(t_job **head, t_job **curr, t_job *j);
void					job_clear(t_job **jobs);

t_job					*job_find(pid_t pid, t_job *job_list);
int						job_stopped(t_job *job);
int						job_completed(t_job *job);

int						job_exec(t_job *j, int fg, t_ctx *ctx);

void					job_wait(t_job *j);
void					job_putbg(t_job *j, int cont);
void					job_putfg(t_job *j, int cont, t_ctx *ctx);

void					job_fmtinfo(t_job *j, char *status);

void					setup_signals(void (*sig)()); 

int						get_path(char *exe, t_ctx *ctx, char **path);

#endif
