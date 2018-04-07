/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_printenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:03:14 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/07 09:28:17 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int		traverse(t_proc *p)
{
//	t_list		*lsts[2];
//	char		*ret;
	int			err;
	int			i;
	size_t		len;
	int			pos;

	err = 0;
//	lsts[0] = NULL;
	i = 1;
	while (p->argv[i] != NULL)
	{
	//	ret = NULL;
		len = ft_strlen(p->argv[i]);
		pos = ft_astr_getkey(p->env, p->argv[i], len);
		if (pos == -1)
		{
			err |= 1;
			ft_dprintf(STDERR_FILENO, "21sh: printenv: '%s' not found\n",
						p->argv[i]);
		}
		else if (p->env[pos][len] == '=')
			ft_printf("%s\n", p->env[pos] + len + 1);
		i++;
	}
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
		i = 0;
		buf = qbuf_new(1 << 8);
		while (p->env[i] != NULL)
		{
			if (ft_strindex(p->env[i], '=') != -1)
			{
				qbuf_add(buf, p->env[i]);
				qbuf_addc(buf, '\n');
			}
			i++;
		}
		qbuf_printclose(&buf, STDOUT_FILENO);
		return (0);
	}
	return (traverse(p));
}
