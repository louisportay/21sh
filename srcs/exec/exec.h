/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 17:25:27 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/24 17:55:06 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <sys/types.h>
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>

# include "tokens.h"
# include "ft_mem.h"
# include "ft_string.h"

# define EXE_LCHD ("launched")

typedef struct s_proc	t_proc;
typedef struct s_job	t_job;

struct					s_proc
{
	struct s_proc		*next;
	char				**argv;
	pid_t				pid;
	char				completed;
	char				stopped;
	int					status;
};

struct					s_job
{
	struct s_job		*next;
	char				*command;
	t_proc				*first_process;
	pid_t				pgid;
	char				notified;
	struct termios		tmodes;
	int					stdin;
	int					stdout;
	int					stderr;
};

t_proc					*proc_new(char **argv);
void					proc_insert(t_proc **head, t_proc **curr, t_proc *p);
int						proc_exec(t_proc *p, pid_t pgid, int fd[3], int fg);

t_job					*job_new(char *cmd, t_proc *plist);
void					job_insert(t_job **head, t_job **curr, t_job *j);

t_job					*job_find(pid_t pid, t_job *job_list);
int						job_isstopped(t_job *job);
int						job_iscompleted(t_job *job);

int						job_exec(t_job *j, int fd, int istty);
void					job_wait(t_job *j);
void					job_putfg(t_job *j, int cont);
void					job_putbg(t_job *j, int cont);
void					job_fmtinfo(t_job *j, char *status);

#endif
