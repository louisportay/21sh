/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 19:18:58 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/23 12:09:54 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int					expand_split(char *str, t_list **lst)
{
	t_list			*l;

	if ((l = bridge_strsplit(str)) == NULL)
		return (-1);
	*lst = l;
	return (0);
}

int					err(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	return (0);
}

int					expand(char *str, t_ctx *ctx,
							void *(*converter)(t_list *lst), void **conv)
{
	t_list			*lst;
	char			*o;

	if (ft_strcmp(str, "") == 0)
		return (1);
	o = ft_strdup(str);
	*conv = NULL;
	if (expand_braces(&o) < 1
		|| expand_tilde(&o, ctx) < 1
		|| expand_param(&o, ctx) < 1
		|| expand_glob(&o, ctx) == -1
		|| expand_split(o, &lst) == -1)
	{
		ft_strdel(&o);
		return (0);
	}
	expand_quotes(lst);
	*conv = (converter != NULL) ? converter(lst) : (void *)lst;
	return (*conv != NULL ? 1 : -1);
}
