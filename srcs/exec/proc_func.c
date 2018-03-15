/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 11:27:18 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/15 16:30:14 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void				proc_foreach(t_proc *p, void (*act)(t_proc *))
{
	while (p != NULL)
	{
		act(p);
		p = p->next;
	}
}

void				proc_foreach_data(t_proc *p, void (*act)(t_proc *, void *),
										void * data)
{
	while (p != NULL)
	{
		act(p, data);
		p = p->next;
	}
}
