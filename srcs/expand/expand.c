/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 19:18:58 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/10 14:51:55 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int					expand_split(char *str, t_list **lst)
{
	t_list			*l;

	if ((l = bridge_strsplit(str)) == NULL)
		return (-1);
	*lst = l;
	return (1);
}

int					err(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	return (0);
}

static void			lcleanup(int ret, int *exp, char **tmp, char **swp)
{
	if (ret > 0)
	{
		ft_strdel(tmp);
		*tmp = *swp;
		*swp = NULL;
		*exp |= 1;
	}
}

int					expand(char *str, t_ctx *ctx, t_list **lst)
{
	char			*tmp;
	char			*swp;
	int				ret;
	int				exp;

	if (ft_strcmp(str, "") == 0)
		return (0);
	exp = 0;
	ret = expand_braces(str, &tmp);
	if (ret == -1)
		return (-3);
	tmp = (ret == 0) ? ft_strdup(str) : tmp;
	exp |= (ret != 0);
	ret = expand_tilde(tmp, &swp, ctx);
	lcleanup(ret, &exp, &tmp, &swp);
	ret = expand_param(tmp, &swp, ctx);
	if (ret == -1)
	{
		ft_strdel(&tmp);
		return (-3);
	}
	lcleanup(ret, &exp, &tmp, &swp);
//	ret = expand_glob(tmp, &swp, ctx);
//	lcleanup(ret, &exp, &tmp, &swp);
	if ((ret = expand_split(tmp, lst)) == -1)
	{
		ft_strdel(&tmp);
		return (-1);
	}
	ft_strdel(&tmp);
	expand_quotes(*lst);
	return (1);
}
