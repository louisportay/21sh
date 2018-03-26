/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_printenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:03:14 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/25 20:34:21 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int		traverse(t_proc *p)
{
	t_list		*lsts[2];
//	char		*str;
	char		*ret;
	int			err;
	int			i;

	err = 0;
	lsts[0] = NULL;
	i = 1;
	while (p->argv[i] != NULL)
	{
		ret = NULL;
		size_t len = ft_strlen(p->argv[i]);
		int pos = ft_astr_getkey(p->env, p->argv[i], len);
		if (pos != -1)
			ft_printf("env[%d]: %s\n", pos, p->env[pos]);
		if (pos == -1)
		{
			err |= 1;
			ft_asprintf(&ret, "221sh: printenv: '%s' not found\n", p->argv[i]);
		}
		else if (p->env[pos][len] == '=')
			ft_asprintf(&ret, "1%s\n", p->env[pos] + len + 1);
		if (ret != NULL)
			ft_list_insert(lsts, lsts + 1, list_create(ret));
		i++;
	}
	p->data.out = lsts[0];
	return (err);
}

int				ft_printenv(t_proc *p, t_ctx *ctx)
{
	int			i;
	t_qbuf		*buf;

	(void)ctx;
	p->type = BUILTIN;
	if (p->argv[1] == NULL)
	{
		p->type = BU_STR;
		i = 0;
		buf = qbuf_new(1 << 8);
		qbuf_addc(buf, '1');
		while (p->env[i] != NULL)
		{
			if (ft_strindex(p->env[i], '=') != -1)
			{
				qbuf_add(buf, p->env[i]);
				qbuf_addc(buf, '\n');
			}
			i++;
		}
		p->data.str = qbuf_del(&buf);//Not freed
		return (0);
	}
	return (traverse(p));
}
