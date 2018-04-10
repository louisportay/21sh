/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exec_argv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 18:08:02 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/10 18:09:22 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int				handle_err(int ret, t_list **lst, char *name)
{
	if (ret == -2)
		ft_dprintf(STDERR_FILENO, "21sh: expand: no match: %s\n", name);
	else
		ft_dprintf(STDERR_FILENO, "21sh: expand: quote error\n");
	ft_list_clear(lst, &ft_memdel);
	return (ret);
}

static void				add_result(t_list **head, t_list **curr, char *av)
{
	char				*s;
	t_list				*e;

	if ((s = ft_strdup(av)) == NULL)
		fatal_err(NOMEM, get_ctxaddr());
	if ((e = list_create(s)) == NULL)
		fatal_err(NOMEM, get_ctxaddr());
	ft_list_insert_last(head, curr, e);
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
				add_result(lst, lst + 1, p->argv[i]);
			if (ret == -2 || ret == -3)
				return (handle_err(ret, lst, p->argv[i]));
		}
		else
			ft_list_insert_last(lst, lst + 1, lst[2]);
		i++;
	}
	ft_astr_clear(&p->argv);
	p->argv = astr_fromlist(lst);
	return (ret);
}
