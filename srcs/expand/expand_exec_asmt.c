/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exec_asmt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 18:06:40 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/20 17:48:32 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

int						expand_asmt(t_proc *p, t_ctx *ctx)
{
	t_asmt				*a;
	int					ret;
	t_list				*lst;

	a = p->asmts;
	while (a != NULL)
	{
		if ((ret = expand(a->value, ctx, &lst)) < 1)
			return (0);
		else
		{
			ft_strdel(&a->value);
			if (lst->next == NULL)
			{
				a->value = lst->content;
				lst->content = NULL;
			}
			else
				a->value = list_flatten(lst);
			ft_list_clear(&lst, &ft_memdel);
		}
		a = a->next;
	}
	return (0);
}
