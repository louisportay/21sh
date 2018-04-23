/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:49:28 by lportay           #+#    #+#             */
/*   Updated: 2018/04/23 13:05:08 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		ft_exit(t_proc *p, t_ctx *ctx, int pipeline)
{
	p->type = BUILTIN;
	if (pipeline == 0)
	{
		if (p->argv[1])
		{
			if (ft_isnumber(p->argv[1]))
				wrap_exit((char)ft_atoi(p->argv[1]), ctx);
			else
			{
				ft_dprintf(STDERR_FILENO, BU_EX_ENUMARG, p->argv[1]);
				wrap_exit(2, ctx);
			}
		}
		else
			wrap_exit(EXIT_SUCCESS, ctx);
		return (0);
	}
	if (p->argv[1] && !ft_isnumber(p->argv[1]))
	{
		ft_dprintf(STDERR_FILENO, BU_EX_ENUMARG, p->argv[1]);
		return (1);
	}
	return ((unsigned char)ft_atoi(p->argv[1]));
}
