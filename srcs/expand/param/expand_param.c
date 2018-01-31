/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 16:48:20 by vbastion          #+#    #+#             */
/*   Updated: 2018/01/14 18:27:16 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

int				expand_param(char **str, t_environ *env)
{
	t_vtok		*toks;
	char		*ret;
	int			v;

	(void)env;
	if (scan_dollar(*str) == 0)
		return (1);
	toks = vtok_get(*str);
	vtok_sanitize(toks);
	if ((v = vtok_handletokens(toks, &ret, env)) == VAR_OK)
	{
		ft_strdel(str);
		*str = ret;
	}
	else if (v == VAR_ERR)
	{
		ft_putendl_fd(ret, STDERR_FILENO);
		ft_strdel(&ret);
	}
	vtok_clear(&toks);
	vtok_addpid(NULL, 1);
	return (v);
}
