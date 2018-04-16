/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 17:25:27 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/12 15:40:26 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <sys/types.h>
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>

# include "ft_42sh.h"
# include "bridge.h"

# define EXE_LCHD ("launched")

# define FTSH_RUN 0
# define FTSH_SIG 1
# define FTSH_EXI 2

typedef struct s_asmt	t_asmt;
typedef struct s_redir	t_redir;
typedef struct s_ctx	t_ctx;

typedef struct s_proc	t_proc;
typedef struct s_job	t_job;

typedef int				(*t_blt)(t_proc *p, t_ctx *ctx, int pipeline);

enum					e_extype
{
	BINARY = 0,
	BUILTIN = 1,
	EXERR = 2,
	EXDIR = EXERR | 4,
	EXPERM = EXERR | 8,
	EXNFD = EXERR | 16,
	EXNFOD = EXERR | 32
};

/*
**	Somewhat legacy, should be removed
*/

union					u_ebin
{
	char				*path;
};

/*
**	In `status` fields of both struct s_proc and struct s_job
**	values are layered as:
**		- from 0x00 to 0xFF	->	exit code
**		- 0x0100			->	completed
**		- 0x0200			->	stopped
**			<<	FOR THE JOB ONLY  >>
**		- 0x0400			->	signaled
**		- 0x0800			->	done
*/

# define JOB_CMP 0x0100
# define JOB_STP 0x0200
# define JOB_SIG 0x0400
# define JOB_DON 0x0800

struct					s_proc
{
	struct s_proc		*next;
	char				**argv;
	char				**env;
	struct s_asmt		*asmts;
	pid_t				pid;
	int					status;
	struct s_redir		*redirs;
	int					pipe_in;
	enum e_extype		type;
	union u_ebin		data;
};

struct					s_job
{
	char				*command;
	struct s_proc		*procs;
	int					status;
	struct s_job		*ok;
	struct s_job		*err;
	struct s_job		*next;
	struct s_job		*parent;
};

int						exec(t_job *jobs);

int						exec_pipe(t_job *j, t_ctx *ctx, int fd);

struct s_proc			*proc_cr(void);
struct s_proc			*proc_new(char **argv);
void					proc_insert(t_proc **head, t_proc **curr, t_proc *p);
void					proc_clear(t_proc **proc);

void					proc_exec(t_proc *p);
void					proc_print(t_proc *p);
int						proc_chgstat(t_job *job, pid_t pid, int status);

void					proc_foreach(t_proc *p, void (*act)(t_proc *));
void					proc_foreach_data(t_proc *p,
											void (*act)(t_proc *, void *),
											void *data);

struct s_job			*job_new(t_proc *plist);
void					job_insert(t_job **head, t_job **curr, t_job *j);
void					job_ctxinsert(t_job *job, t_ctx *ctx);

struct s_job			*job_find(pid_t pid, t_job *job_list);
int						job_stopped(t_job *job);
int						job_completed(t_job *job);

int						job_wait(t_job *j);
int						job_putfg(t_job *j, t_ctx *ctx);

void					job_fmtinfo(t_job *j, char *status);

int						job_next(t_job *j, t_ctx *ctx);
int						job_donext(t_job *j, t_ctx *ctx);

void					*job_safeclear(t_job **job);

void					prefork_assign(t_ctx *ctx, t_asmt *asmt);
int						proc_update_env(t_proc *p);
void					handle_assign(char ***astrenv, t_asmt *asmt,
										int *locpath);

char					*path_fromcache(char *exe, t_ctx *ctx);
char					*proc_path(t_proc *p, t_ctx *ctx, int locpath);
int						prepare_fork(t_proc *p, t_ctx *ctx, int pipeline);

char					*get_command(t_job *j);

int						do_redir(t_redir *r, int fd[3], int *pipes);
int						r_andgreat_anddgreat(t_redir *r);
int						r_greatand_lessand(t_redir *r, int fd[3], int *pipes);
int						err_close_fd(int fd);
int						err_open(char *s);
int						err_busyfd(int	fd);
int						err_tmpfile(void);
int						err_badfd(char *fd);

int						job_exec(t_job *j, t_ctx *ctx);
int						job_exec_loop(t_job **job, t_ctx *ctx, int exp_err);
int						job_one(t_job *j, t_ctx *ctx);
int						job_pipe(t_job *j, t_ctx *ctx);

char					*job_last_argv(t_job *j);

void					exec_print_err(enum e_extype type, char *path);

void					clear_pipe(t_job *j, t_proc *last, int fd);

void					restore_fds(t_ctx *ctx);

int						expand_redir(t_proc *p, t_ctx *ctx);
int						expand_argv(t_proc *p, t_ctx *ctx);
int						expand_asmt(t_proc *p, t_ctx *ctx);

#endif
