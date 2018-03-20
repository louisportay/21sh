/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 10:30:48 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/20 09:21:36 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

#define JOB_NO "no job"
#define JOB_PRE "previous job"
#define JOB_LAST "last job"

#define BU_JOB_AMB ("ambiguous job spec")
#define BU_JOB_NO ("no such job")
#define BU_JOB_ERR ("221sh: %s: %s\n")

typedef struct s_job	t_job;
typedef struct s_ctx	t_ctx;

void					jc_signal(int signo);
int						jc_updatepipe(t_job *j);
void					jc_updateproc(t_job *j, t_proc *p, int status);

int						jc_procfind(t_job *j, pid_t pid, t_proc **p);
int						jc_jobfind(t_ctx *ctx, pid_t pid, t_proc **p);
size_t					jc_ctxfind(t_ctx *ctx, int pgid);

void					jc_print(t_ctx *ctx, int all, int verbose);
void					jc_notify(t_job *j, t_ctx *ctx, int i, int all);
size_t					jc_findid(t_ctx *ctx, t_job *j);
char					jc_getstatus(t_job *j);

void					jc_updatebg(t_ctx *ctx);
void					jc_updatebgjob(t_ctx *ctx, t_job *j, size_t i);

size_t					jc_getbgnext(t_ctx *ctx);
size_t					jc_bggrow(t_ctx *ctx);

size_t					jc_addtobg(t_ctx *ctx, t_job *j);
void					jc_rmbg(t_ctx *ctx, t_job *j);

t_job					*jc_jobspec(t_proc *p, char *caller, char *argv,
									t_ctx *ctx);

void					jc_restore(t_job *j, t_proc *caller, t_list **curr);

void					jc_remove(t_ctx *ctx, t_job *job, size_t i);

#endif
