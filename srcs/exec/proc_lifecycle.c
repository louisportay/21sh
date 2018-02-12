/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_lifecycle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 13:38:51 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/12 18:51:31 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_proc					*proc_new(char **argv)
{
	t_proc				*proc;

	if ((proc = (t_proc *)ft_memalloc(sizeof(t_proc))) == NULL)
		return (NULL);
	proc->argv = argv;
	return (proc);
}

void					proc_insert(t_proc **head, t_proc **curr, t_proc *p)
{
	if (*head == NULL)
		*head = p;
	else
		(*curr)->next = p;
	*curr = p;
}

void					proc_clear(t_proc **proc)
{
	t_proc				*p;
	t_proc				*tmp;

	p = *proc;
	*proc = NULL;
	while (p != NULL)
	{
		tmp = p;
		p = p->next;
		ft_memdel((void **)&tmp);
	}
}
