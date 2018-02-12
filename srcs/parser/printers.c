/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptok_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 12:56:29 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/12 11:10:34 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void					ptok_print(struct s_ptok *tokens)
{
	if (tokens->job != NULL)
		job_print(tokens->job);
	if (tokens->ok != NULL)
	{
		printf("-- && --\n");
		ptok_print(tokens->ok);
	}
	if (tokens->err != NULL)
	{
		printf("-- || --\n");
		ptok_print(tokens->err);
	}
	if (tokens->next != NULL)
		ptok_print(tokens->next);
}

void					asmt_print(t_asmt *asmt)
{
	while (asmt != NULL)
	{
		printf("%s=%s\n", asmt->key, asmt->value);
		asmt = asmt->next;
	}
}

void					astr_print(char **astr)
{
	int					i;

	i = 0;
	while (astr[i] != NULL)
	{
		printf("argv[%d]: %s\n", i, astr[i]);
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
			printf("%s=%s ", asmt->key, asmt->value);
			asmt = asmt->next;
		}
		while (proc->argv[i] != NULL)
		{
			printf("%s ", proc->argv[i]);
			i++;
		}
		printf("\nREDIRS:\n");
		redir_print(proc->redirs);
		printf("\n");
		proc = proc->next;
	}
}

void					redir_print(t_redir *redir)
{
	while (redir != NULL)
	{
		printf("\tleft: %d - right: %s | %d - has dash: %d\n",
				redir->lhs, redir->s_rhs, redir->fd_rhs, redir->dash);
		redir = (t_redir *)redir->next;
	}
}
