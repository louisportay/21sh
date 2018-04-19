/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptok_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 12:56:29 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/19 10:14:14 by vbastion         ###   ########.fr       */
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
	t_proc				*p;

	while (job != NULL)
	{
		if (job->type == JOB_HEAD || job->type == JOB_OK)
			ft_printf("%s\n", job->type == JOB_HEAD ? "JOB_HEAD" : "JOB_OK");
		else if (job->type == JOB_ERR)
			ft_printf("JOB_ERR\n");
		else
			ft_printf("UNTAGGED JOB\n");
		p = job->procs;
		while (p != NULL)
		{
			asmt_print(p->asmts);
			astr_print(p->argv);
			if (p->redirs != NULL)
			{
				ft_printf("\nREDIRS:\n");
				redir_print(p->redirs);
				ft_printf("\n");
			}
			p = p->next;
		}
		job = job->next;
	}
}
