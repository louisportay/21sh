/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_glob.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 13:05:54 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/21 13:06:45 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"

static int		matching_bracket(char *s, t_stack *quote)
{
	char		*opening_bracket;

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

int				scan_glob(char *s)
{
	t_stack		*quote;

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
