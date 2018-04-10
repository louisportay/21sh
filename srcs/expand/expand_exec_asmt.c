/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exec_asmt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 18:06:40 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/10 18:11:45 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int				err_expand(int ret, char *val)
{
	if (ret == -1)
		on_emem(NOMEM);
	else if (ret == -2)
	{
		ft_dprintf(STDERR_FILENO, "21sh: no match: %s\n", val);
		return (-2);
	}
	else if (ret == -3)
	{
		ft_dprintf(STDERR_FILENO, "21sh: expand: quote error\n");
		return (-3);
	}
	return (-1);
}

int						expand_asmt(t_proc *p, t_ctx *ctx)
{
	t_asmt				*a;
	int					ret;
	t_list				*lst;

	a = p->asmts;
	while (a != NULL)
	{
		if ((ret = expand(a->value, ctx, &lst)) < 1)
			return (err_expand(ret, a->value));
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
