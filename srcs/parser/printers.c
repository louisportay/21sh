/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptok_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 12:56:29 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/25 20:39:26 by vbastion         ###   ########.fr       */
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

void					job_print(t_job *job)
{
	t_proc				*proc;
	t_asmt				*asmt;
	int					i;

	proc = job->procs;
	while (proc != NULL)
	{
		asmt = proc->asmts;
		i = 0;
		while (asmt != NULL)
		{
			ft_printf("%s=%s ", asmt->key, asmt->value);
			asmt = asmt->next;
		}
		while (proc->argv[i] != NULL)
		{
			ft_printf("%s ", proc->argv[i]);
			i++;
		}
		ft_printf("\nREDIRS:\n");
		redir_print(proc->redirs);
		ft_printf("\n");
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
