/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set_args.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 17:37:09 by vbastion          #+#    #+#             */
/*   Updated: 2018/04/12 16:54:07 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			set_help(t_proc *p, int usage)
{
	p->type = BUILTIN;
	if (usage)
		ft_putendl_fd(BU_S_USG, STDERR_FILENO);
	ft_printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
				BU_S_HPR, BU_S_HSE, BU_S_HEX, BU_S_HBG, BU_S_HON, BU_S_HFN,
				BU_S_HDO, BU_S_HNU, BU_S_HFA, BU_S_HEL);
	return (-1);
}

static int	lget_switch(int opts[2], t_proc *p, int i, u_short *tmp)
{
	if (p->argv[i][0] == '-')
	{
		if ((opts[1] = get_min(p, i, tmp)) == -1)
			return (-1);
	}
	else if (p->argv[i][0] == '+')
	{
		if ((opts[1] = get_max(p, i, tmp)) == -1)
			return (-1);
	}
	if (opts[1] & BU_SET_HELP)
		return (set_help(p, (opts[1] & BU_SET_USAGE) != 0));
	opts[0] |= opts[1];
	return (0);
}

int			bu_set_getopts(t_proc *p, t_ctx *ctx, int i)
{
	int				opts[2];
	u_short			tmp;

	opts[0] = 0;
	tmp = ctx->set;
	while (p->argv[i] != NULL)
	{
		if ((p->argv[i][0] == '-' || p->argv[i][0] == '+')
				&& ft_isalpha(p->argv[i][1]))
			lget_switch(opts, p, i, &tmp);
		else if (p->argv[i][0] == '-' || p->argv[i][0] == '+')
		{
			ft_dprintf(STDERR_FILENO, "21sh: set: %s: Invalid argument\n%s\n",
						p->argv[i], BU_S_USG);
			return (-1);
		}
		else
			break ;
		i++;
	}
	ctx->set = tmp;
	return (opts[0]);
}
