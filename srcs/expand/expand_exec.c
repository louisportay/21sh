/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:05:27 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/23 22:49:06 by vbastion         ###   ########.fr       */
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
		if ((ret = expand(p->argv[i], ctx, NULL, (void **)lst + 2)) < 1)
		{
			if (ret == -1)
				on_emem(NOMEM);
			else if (ret == 0)
				lst[2] = list_create(ft_strdup(p->argv[i]));
			else if (ret == -2)
			{
				dprintf(STDERR_FILENO, "21sh: no match: %s\n", p->argv[i]);
				ft_list_clear(lst, &ft_memdel);
				return (-2);
			}
		}
		else
			ft_list_insert_last(lst, lst + 1, lst[2]);
		i++;
	}
	ft_astr_clear(&p->argv);
	p->argv = astr_fromlist(lst);
	return (ret);
}

//	static void				*flatten_list(t_list *l)
//	{
//		t_qbuf				*buf;
//	
//		buf = qbuf_new(1 << 8);
//		while (l != NULL)
//		{
//			qbuf_add(buf, (char *)l->content);
//			if (l->next != NULL)
//				qbuf_addc(buf, ' ');
//			l = l->next;
//		}
//		return ((void *)qbuf_del(&buf));
//	}

//	int						expand_asmt(t_proc *p, t_ctx *ctx)
//	{
//		t_asmt				*a;
//		char				*s;
//		int					ret;
//	
//		a = p->asmts;
//		while (a != NULL)
//		{
//			if ((ret = expand(a->value, ctx, &flatten_list, (void **)&s)) < 1)
//			{
//				if (ret == -1)
//					on_emem(NOMEM);
//				else if (ret == -2)
//				{
//					dprintf(STDERR_FILENO, "21sh: no match: %s\n", a->value);
//					return (-2);
//				}
//			}
//			else
//			{
//				ft_strdel(&a->value);
//				a->value = s;
//			}
//			a = a->next;
//		}
//		return (0);
//	}
//	
//	int						expand_redir(t_proc *p, t_ctx *ctx)
//	{
//		t_redir				*r;
//		t_list				*l;
//	
//		r = p->redirs;
//		while (r != NULL)
//		{
//			if (r->type != DLESS)
//			{
//				if ((ret = expand(r->s_rhs, ctx, NULL, (void **)&l)) < 1)
//				{
//					if (ret == -1)
//						on_emem(NOMEM);
//					else if (ret == -2)
//					{
//						dprintf(STDERR_FILENO, "21sh: no match: %s\n", a->value);
//						return (-2);
//					}
//				}
//				else
//				{
//					if (l->next != NULL)
//					{
//						r->type = TOKERR;
//						ft_list_clear(&l, &ft_memdel);
//					}
//					else
//					{
//						ft_strdel(&r->s_rhs);
//						r->s_rhs = (char *)l->content;
//						ft_memdel((void **)&l);
//					}
//				}
//			}
//			r = r->next;
//		}
//		return (0);
//	}

int expand_redir(t_proc *p, t_ctx *ctx) { (void)p; (void)ctx; return (0); }
int expand_asmt(t_proc *p, t_ctx *ctx) { (void)p; (void)ctx; return (0); }

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

int						expand_job(t_job *j, t_ctx *ctx, int *exp_err)
{
	t_proc				*p;
	int					status;

	if (j == NULL)
		return (0);
	p = j->procs;
	*exp_err = 0;
	while (p != NULL)
	{
		if ((status = expand_proc(p, ctx)) == 1)
			*exp_err = 1;
		p = p->next;
	}
	return (status);
}
