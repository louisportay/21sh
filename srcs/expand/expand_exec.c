/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 15:05:27 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/10 11:37:49 by vbastion         ###   ########.fr       */
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
		if ((ret = expand(p->argv[i], ctx, lst + 2)) < 1)
		{
			if (ret == -1)
				on_emem(NOMEM);
			else if (ret == 0 && (ctx->set & NULLGLOB) == 0)
			{
				lst[2] = list_create(ft_strdup(p->argv[i]));
				ft_list_insert_last(lst, lst + 1, lst[2]);
			}
			else if (ret == -2)
			{
				ft_dprintf(STDERR_FILENO, "21sh: no match: %s\n", p->argv[i]);
				ft_list_clear(&lst[0], &ft_memdel);
				return (-2);
			}
			else if (ret == -3)
			{
				ft_dprintf(STDERR_FILENO, "21sh: expand: quote error\n");
				ft_list_clear(&lst[0], &ft_memdel);
				return (-3);
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

int						expand_asmt(t_proc *p, t_ctx *ctx)
{
	t_asmt				*a;
	int					ret;
	t_list				*lst;

	a = p->asmts;
	while (a != NULL)
	{
		if ((ret = expand(a->value, ctx, &lst)) < 1)
		{
			if (ret == -1)
				on_emem(NOMEM);
			else if (ret == -2)
			{
				ft_dprintf(STDERR_FILENO, "21sh: no match: %s\n", a->value);
				return (-2);
			}
			else if (ret == -3)
			{
				ft_dprintf(STDERR_FILENO, "21sh: expand: quote error\n");
				return (-3);
			}
		}
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
			{
				if (ret == -1)
					on_emem(NOMEM);
				else if (ret == -2)
				{
					r->type = TOKERR;
					ft_dprintf(STDERR_FILENO, "21sh: no match: %s\n", r->s_rhs);
					return (-2);
				}
				else if (ret == -3)
				{
					r->type = TOKERR;
					ft_dprintf(STDERR_FILENO, "21sh: expand: quote error\n");
					return (-3);
				}
			}
			else
			{
				if (((char *)l->content)[0] == '\0'
					|| l->next != NULL)
				{
					r->type = TOKERR;
					ft_list_clear(&l, &ft_memdel);
					return (0);
				}
				ft_strdel(&r->s_rhs);
				r->s_rhs = (char *)l->content;
				ft_memdel((void **)&l);
			}
		}
		r = (t_redir *)r->next;
	}
	return (0);
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
