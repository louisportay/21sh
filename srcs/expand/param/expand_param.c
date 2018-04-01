/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 16:48:20 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/01 12:48:26 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

int				expand_param(char *str, char **ret, t_ctx *ctx)
{
	t_vtok		*toks;
	char		*r;
	int			v;

	if (scan_dollar(str) == 0)
		return (0);
	toks = vtok_get(str);
	vtok_sanitize(toks);
	if ((v = vtok_handletokens(toks, &r, ctx)) == VAR_OK)
		*ret = r;
	else if (v == VAR_ERR)
		ft_putendl_fd(r, STDERR_FILENO);
	vtok_clear(&toks);
	vtok_addpid(NULL, 1);
	return (1);
}
