/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 16:47:01 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/20 18:09:50 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

static int		matching_bracket(char *s, t_stack *quote)
{
	char *opening_bracket;

	opening_bracket = s++;
	quote = stack_dup(quote);
	while (*s)
	{
		if (quote->state == BSLASH && *s != '\\')
			stack_pop(&quote);
		if (*s == '\\' || *s == '\'' || *s == '\"')
			update_linestate(&quote, *s);
		if (*s == ']' && quote->state == UNQUOTED && s - 1 != opening_bracket)
		{
			stack_del(&quote);
			return (1);
		}
		s++;
	}
	stack_del(&quote);
	return (0);
}

static int		scan_glob(char *s)
{
	t_stack *quote;

	quote = NULL;
	if (stack_create_push(&quote, UNQUOTED) == -1)
		fatal_err(NOMEM, get_ctxaddr());
	while (*s != '\0')
	{
		if (*s == '\\' || *s == '\'' || *s == '\"')
			update_linestate(&quote, *s);
		if (quote->state == BSLASH && *s != '\\')
			stack_pop(&quote);
		else if ((*s == '*' || *s == '?') && quote->state == UNQUOTED)
		{
			stack_del(&quote);
			return (1);
		}
		else if (*s == '[' && matching_bracket(s, quote) == 1)
		{
			stack_del(&quote);
			return (1);
		}
		s++;
	}
	stack_del(&quote);
	return (0);
}

static void		multi_expand_loop(char **s, t_list **lst)
{
	t_list		*news;
	t_list		*t;
	t_list		*next;

	news = bridge_strsplit(*s);
	ft_strdel(s);
	(*lst)->content = news->content;
	if (news->next == NULL)
	{
		free(news);
		*lst = (*lst)->next;
	}
	else
	{
		news->content = NULL;
		t = news;
		news = news->next;
		free(t);
		t = ft_list_last(news);
		next = (*lst)->next;
		(*lst)->next = news;
		t->next = next;
	}
}

static int		multi_expand(t_list *lst)
{
	char		*s;
	int			ret;

	while (lst != NULL)
	{
		s = (char *)lst->content;
		if ((ret = scan_glob(s)) == -1)
			return (-1);
		else if (ret == 0)
		{
			lst->content = (void *)s;
			lst = lst->next;
		}
		else if (ret == 1)
		{
			ret = do_expand_glob(&s);
			if (ret == 0)
			{
				lst->content = (void *)s;
				lst = lst->next;
				return (0);
			}
			else
				multi_expand_loop(&s, &lst);
		}
	}
	return (1);
}

int				expand_glob(t_list *lst, t_ctx *ctx)
{
	int			r;

	if (ctx->set & BU_SET_FNEXP)
		return (0);
	if (lst == NULL)
		return (0);
	if ((r = multi_expand(lst)) < 1)
	{
		ft_list_clear(&lst, &ft_memdel);
		if (r == -1)
			return (-1);
		if (ctx->set & FAILGLOB)
			return (-2);
		else if (ctx->set & NULLGLOB)
			return (-4);
		return (0);
	}
	return (1);
}
