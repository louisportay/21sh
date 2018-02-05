/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 19:18:58 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/14 18:08:47 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int					expand_split(char **str, t_list **lst)
{
	t_list			*l;

	if ((l = bridge_strsplit(*str)) == NULL)
		return (0);
	ft_strdel(str);
	*lst = l;
	return (1);
}

int					err(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	return (0);
}

int					expand(char **str, t_environ *env,
							void *(*converter)(t_list *lst), void **conv)
{
	t_list	*lst;
	char	*o;

	if (ft_strcmp(*str, "") == 0)
		return (1);
	o = ft_strdup(*str);
	if (expand_braces(str) < 1
		|| expand_tilde(str, env) < 1
		|| expand_param(str, env) < 1
		|| expand_glob(str) == -1)
	{
		ft_strdel(str);
		*str = 0;
		return (0);
	}
	ft_strdel(&o);
	*conv = NULL;
	if ((expand_split(str, &lst)) > 0)
	{
		expand_quotes(lst);
		*conv = converter(lst);
		return (*conv != NULL ? 1 : -1);
	}
	return (0);
}
