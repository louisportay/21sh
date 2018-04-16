/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 18:58:08 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/10 09:29:42 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_42sh.h"

static int				hash_invalid_arg(char *s)
{
	ft_dprintf(STDERR_FILENO, "42sh: hash: '%s': Invalid argument\n", s);
	return (-1);
}

static int				lget_opt(t_proc *p, t_ctx *ctx, int i, int *f)
{
	int					j;

	j = 1;
	if (p->argv[i][j] == '-')
		return (hash_invalid_arg(p->argv[1]));
	while (p->argv[i][j] != '\0')
	{
		if (p->argv[i][j] == 'r')
			*f |= BU_H_CLR;
		else if (p->argv[i][j] == 'p')
			return (hash_inh(p, ctx, i, j) == 0 ? -2 : -1);
		else if (p->argv[i][j] == 'd' && (*f & BU_H_PRT) == 0)
			*f |= BU_H_DEL;
		else if (p->argv[i][j] == 't')
			*f = (*f & ~BU_H_DEL) | BU_H_PRT;
		else if (p->argv[i][j] == 'l')
			*f |= BU_H_LST;
		else
		{
			ft_dprintf(STDERR_FILENO, BU_H_EINVAL, p->argv[i][j], BU_H_USAGE);
			return (-1);
		}
		j++;
	}
	return (0);
}

int						bu_hash_getopts(t_proc *p, t_ctx *ctx, int *i)
{
	int					f;
	int					t;

	f = 0;
	while (p->argv[*i] != NULL)
	{
		if (p->argv[*i][0] == '-')
		{
			if ((t = lget_opt(p, ctx, *i, &f)) < 0)
				return (t);
		}
		else
			break ;
		(*i)++;
	}
	return (f);
}
