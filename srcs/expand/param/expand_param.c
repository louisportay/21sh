/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <vbastion@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 16:48:20 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/12 12:48:36 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand_param.h"

static int		lquoterr(void)
{
	ft_dprintf(STDERR_FILENO, "42sh: expand: param: Missing quote\n");
	return (-1);
}

static int		lerr(t_vtok **toks)
{
	vtok_clear(toks);
	return (-1);
}

int				expand_param(char *str, char **ret, t_ctx *ctx)
{
	t_vtok		*toks;
	char		*r;
	int			v;
	int			err;
	int			rval;

	if ((rval = scan_dollar(str)) == 0)
		return (0);
	else if (rval == -1)
		return (lquoterr());
	err = 0;
	toks = vtok_get(str, &err);
	*ret = NULL;
	if (err)
		return (lquoterr());
	err = 0;
	if (vtok_sanitize(toks, 0, &err))
		return (lerr(&toks));
	if ((v = vtok_handletokens(toks, &r, ctx)) == VAR_OK)
		*ret = r;
	else if (v == VAR_ERR)
		ft_putendl_fd(r, STDERR_FILENO);
	vtok_clear(&toks);
	vtok_addpid(NULL, 1);
	return (1);
}
