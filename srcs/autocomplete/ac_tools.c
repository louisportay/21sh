/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 19:53:16 by lportay           #+#    #+#             */
/*   Updated: 2018/04/13 14:12:09 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	expand_tilde_autocomplete(char **s, char *home)
{
	char	*expanded_s;

	if ((expanded_s = ft_strexpand(*s, '~', home)) == NULL)
		fatal_err(NOMEM, get_ctxaddr());
	if (expanded_s != *s)
	{
		free(*s);
		*s = expanded_s;
	}
}

int		dlst_hasblank(t_dlist *dlst)
{
	while (dlst->prev)
	{
		if (ft_isblank(*(char *)dlst->data) == 1)
			return (1);
		dlst = dlst->prev;
	}
	return (0);
}

int		entry_already_in_list(char *name, t_dlist *matches)
{
	while (matches)
	{
		if (ft_strcmp(name, (char *)matches->data) == 0)
			return (1);
		matches = matches->next;
	}
	return (0);
}
