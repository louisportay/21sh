/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 17:25:27 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/16 20:24:21 by vbastion         ###   ########.fr       */
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

# include "ft_21sh.h"

# define EXE_LCHD ("launched")

# define FTSH_RUN 0
# define FTSH_SIG 1
# define FTSH_EXI 2

typedef struct s_asmt	t_asmt;
typedef struct s_redir	t_redir;
typedef struct s_ctx	t_ctx;

typedef struct s_proc	t_proc;
typedef struct s_job	t_job;

typedef int				(*t_blt)(t_proc *p, t_ctx *ctx);

enum					e_extype
{
	BINARY,
	BUILTIN,
	EXERR
};

union					u_ebin
{
	char				*path;
	struct s_list		*out;
};

struct					s_proc
{
	struct s_proc		*next;
	char				**argv;
	char				**env;
	struct s_asmt		*asmts;
	pid_t				pid;
	char				completed;
	char				stopped;
	int					status;
	struct s_redir		*redirs;
	enum e_extype		type;
	union u_ebin		data;
};

struct					s_job
{
	char				*command;
	struct s_proc		*procs;
	pid_t				pgid;
	char				notified;
	struct termios		tmodes;
	int					status;
	int					stdin;
	int					stdout;
	int					stderr;
	int					fg;
	struct s_job		*ok;
	struct s_job		*err;
	struct s_job		*next;
	struct s_job		*parent;
};

struct s_proc			*proc_cr(void);
struct s_proc			*proc_new(char **argv);
void					proc_insert(t_proc **head, t_proc **curr, t_proc *p);
void					proc_clear(t_proc **proc);

void					proc_exec(t_proc *p, pid_t pgid, int fd[3], int fg,
									t_ctx *ctx);
int						proc_chgstat(t_job *job, pid_t pid, int status);

struct s_job			*job_new(t_proc *plist);
void					job_insert(t_job **head, t_job **curr, t_job *j);
void					*job_clear(t_job **jobs);

struct s_job			*job_find(pid_t pid, t_job *job_list);
int						job_stopped(t_job *job);
int						job_completed(t_job *job);

int						job_exec(t_job *j, int fg, t_ctx *ctx);

int						job_wait(t_job *j);
void					job_putbg(t_job *j, int cont);
int						job_putfg(t_job *j, int cont, t_ctx *ctx);

void					job_fmtinfo(t_job *j, char *status);

int						job_next(t_job *j, t_ctx *ctx);

void					setup_signals(void (*sig)()); 

void					prefork_assign(t_ctx *ctx, t_asmt *asmt);
int						proc_update_env(t_proc *p);
void					handle_assign(char ***astrenv, t_asmt *asmt,
										int *locpath);

void					astr_to_buf(char **argv, t_qbuf *buf, int last);
void					astr_env_replace(char ***env, char *key, char *new_v);

int						get_path(char *exe, char **env, char **path,
									int locpath);
int						ctx_path(char *exe, t_ctx *ctx, char **path);
int						loc_path(char *exe, char **env, char **path);

char					*proc_path(t_proc *p, t_ctx *ctx, int locpath);
int						prepare_fork(t_proc *p, t_ctx *ctx);

int						blt_output(t_proc *p);

#endif
