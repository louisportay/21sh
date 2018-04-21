/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:05:27 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/20 18:41:51 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

void					ft_list_insert_last(t_list **head, t_list **curr,
											t_list *lst)
{
	t_list				*last;

	last = lst->next != NULL ? ft_list_last(lst) : lst;
	if (*head == NULL)
		*head = lst;
	else
		(*curr)->next = lst;
	*curr = last;
}

int						expand_proc(t_proc *p, t_ctx *ctx)
{
	if (expand_argv(p, ctx) == -2)
		return (1);
	else if (expand_asmt(p, ctx) == -2)
		return (1);
	else if (expand_redir(p, ctx) == -2)
		return (1);
	return (0);
}

int						expand_job(t_job *j, t_ctx *ctx)
{
	t_proc				*p;
	int					status;

	if (j == NULL)
		return (0);
	p = j->procs;
	while (p != NULL)
	{
		if ((status = expand_proc(p, ctx)) == 1)
			p->is_err = 1;
		p = p->next;
	}
	return (status);
}
