/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exec_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 17:58:30 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/20 17:49:23 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int				ok_expand(t_list **l, t_redir *r)
{
	if (((char *)((*l)->content))[0] == '\0' || (*l)->next != NULL)
	{
		r->type = TOKERR;
		ft_list_clear(l, &ft_memdel);
		return (0);
	}
	ft_strdel(&r->s_rhs);
	r->s_rhs = (char *)((*l)->content);
	ft_memdel((void **)l);
	return (1);
}

int						expand_redir(t_proc *p, t_ctx *ctx)
{
	t_redir				*r;
	t_list				*l;
	int					ret;

	r = p->redirs;
	while (r != NULL)
	{
		if (r->type != DLESS)
		{
			if ((ret = expand(r->s_rhs, ctx, &l)) < 1)
				return (0);
			else
			{
				if (ok_expand(&l, r) == 0)
					return (0);
			}
		}
		r = (t_redir *)r->next;
	}
	return (0);
}
