/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:05:27 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/21 19:42:18 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

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

int						expand_argv(t_proc *p, t_ctx *ctx)
{
	int					i;
	t_list				*lst[3];
	int					ret;

	ret = 0;
	i = 0;
	lst[0] = NULL;
	while (p->argv[i] != NULL)
	{
		ret |= expand(p->argv[i], ctx, NULL, (void **)(lst + 2));
		ft_list_insert_last(lst, lst + 1, lst[2]);
		i++;
	}
	ft_astr_clear(&p->argv);
	p->argv = astr_fromlist(lst);
	return (ret);
}

int						expand_asmt(t_proc *p, t_ctx *ctx)
{
	(void)p;
	(void)ctx;
	return (0);
}

int						expand_proc(t_proc *p, t_ctx *ctx)
{
	if (expand_argv(p, ctx) == -1 || expand_asmt(p, ctx) == -1)
		return (-1);
	return (0);
}

int						expand_job(t_job *j, t_ctx *ctx)
{
	if (j == NULL)
		return (0);
	if (expand_proc(j->procs, ctx) == 1)
		return (1);
	if (expand_job(j->ok, ctx) == 1)
		return (1);
	if (expand_job(j->err, ctx) == 1)
		return (1);
	return (0);
}
