/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 10:30:48 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/27 11:41:01 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

typedef struct s_job	t_job;
typedef struct s_ctx	t_ctx;

int						jc_getnext(t_job *j, t_job **next, int *status);
void					jc_signal(int signo);

t_job					*jc_getchild(t_job *j, pid_t pid, t_job **child);
t_job					*jc_getparent(t_ctx *ctx, pid_t pid, t_job **child);

void					jc_print(t_ctx *ctx);

void					jc_addjobs(t_job *jobs, t_ctx *ctx);

void					jc_update(t_job *j, t_job *parent, pid_t pid,
									int status);

#endif
