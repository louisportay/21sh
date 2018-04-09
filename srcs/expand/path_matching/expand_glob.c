/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 16:47:01 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/09 10:20:32 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pattern_matching.h"
#include "dir_explorer.h"

static int             matching_bracket(char *s, t_stack *quote)
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



static int             scan_glob(char *s)
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

static int		multi_expand(t_list *lst)
{
	char		*s;
	int			ret;

	while (lst != NULL)
	{
		s = (char *)lst->content;
		if (scan_glob(s) == 1)
		{
			//	printf("RET=1\n");
			if ((ret = do_expand_glob(&s)) < 1)
				return (ret);
		}
		//	printf("RET=0\n");
		lst->content = (void *)s;
		lst = lst->next;
	}
	return (1);
}

static char		*bufferize(t_list *lst)
{
	t_qbuf		*buf;

	buf = qbuf_new(128);
	while (lst != NULL)
	{
		qbuf_add(buf, (char *)lst->content);
		lst = lst->next;
		if (lst != NULL)
			qbuf_addc(buf, ' ');
	}
	return (qbuf_del(&buf));
}

int				expand_glob(char *str, char **ret, t_ctx *ctx)
{
	t_list		*lst;
	int			r;

	if (ctx->set & BU_SET_FNEXP)
		return (0);
	if (str == NULL || *str == '\0')
		return (0);
	lst = bridge_strsplit(str);
	if ((r = multi_expand(lst)) < 1)
	{
		ft_list_clear(&lst, &ft_memdel);
		if (r == -1)
			return (-1);
		if (ctx->set & FAILGLOB)
			return (-2);
		else if (ctx->set & NULLGLOB)
			return (-3);
		return (0);
	}
	*ret = bufferize(lst);
	ft_list_clear(&lst, &ft_memdel);
	return (*ret == NULL ? -1 : 1);
}
