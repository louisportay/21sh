/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptok_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 12:56:29 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/18 19:30:57 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void					asmt_print(t_asmt *asmt)
{
	while (asmt != NULL)
	{
		ft_printf("%s=%s\n", asmt->key, asmt->value);
		asmt = asmt->next;
	}
}

void					astr_print(char **astr)
{
	int					i;

	i = 0;
	while (astr[i] != NULL)
	{
		ft_printf("argv[%d]: %s\n", i, astr[i]);
		i++;
	}
}

void					job_printall(t_job *job)
{
	ft_printf("ALL JOBS\n");
	while (job != NULL)
	{
		job_print_cmd(job);
		job = job->forward;
	}
}

void					job_print(t_job *job)
{
	t_proc				*proc;

	proc = job->procs;
	while (proc != NULL)
	{
		asmt_print(proc->asmts);
		astr_print(proc->argv);
		if (proc->redirs != NULL)
		{
			ft_printf("\nREDIRS:\n");
			redir_print(proc->redirs);
			ft_printf("\n");
		}
		proc = proc->next;
	}
}

void					redir_print(t_redir *redir)
{
	while (redir != NULL)
	{
		ft_printf("\tleft: %d - right: %s | %d - has dash: %d\n",
					redir->lhs, redir->s_rhs, redir->fd_rhs, redir->dash);
		redir = (t_redir *)redir->next;
	}
}

void					job_print_cmd(t_job *job)
{
	while (job != NULL)
	{
		if (job->type == JOB_HEAD)
			ft_printf("JOB_HEAD\n");
		else if (job->type == JOB_OK)
			ft_printf("JOB_OK\n");
		else if (job->type == JOB_ERR)
			ft_printf("JOB_ERR\n");
		else
			ft_printf("UNTAGGED JOB\n");
		job_print(job);
		job = job->next;
	}
}
