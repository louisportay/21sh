/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 10:30:48 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/27 17:24:44 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

/*
**	#define JC_NUL -1
**	#define JC_STP 0
**	#define JC_RUN 1
**	#define JC_TODO 2
**	#define JC_DONE 3
**	#define JC_ERR 4
**	#define JC_SIGNAL 5
*/

typedef struct s_job	t_job;
typedef struct s_ctx	t_ctx;

/*
**	int						jc_getnext(t_job *j, t_job **next, int *status);
**	void					jc_signal(int signo);
**	
**	t_job					*jc_getjob(t_ctx *ctx, pid_t pid);
**	
**	void					jc_print(t_ctx *ctx);
**	
**	void					jc_addjobs(t_job *jobs, t_ctx *ctx);
**	
**	void					jc_update(t_job *j, pid_t pid, int status);
**	
**	int						jc_stped(t_job *j);
**	int						jc_cpled(t_job *j);
**	
**	int						jc_status(t_job *j);
**	
**	int						jc_getstatus(t_job *j);
**	int						jc_pipestatus(t_job *j);
*/

void					jc_updateall(t_ctx *ctx);
void					jc_updateone(t_job *j);
void					jc_updatepipe(t_job *j);
void					jc_updateproc(t_job *j, t_proc *p, int status);
void					jc_signal(int signo);
void					jc_addjobs(t_job *jobs, t_ctx *ctx);
void					jc_print(t_ctx *ctx);

#endif
