/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:49:28 by lportay           #+#    #+#             */
/*   Updated: 2018/03/15 15:15:13 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//To finish

int		ft_exit(t_proc *p, t_ctx *ctx)
{
	p->type = BU_STR;
//	if (pas de pipe)
//	{
		if (p->argv[1])
		{
			if (ft_isnumber(p->argv[1]))
			{
				asprintf(&p->data.str, "2exit\n");
				wrap_exit((char)ft_atoi(p->argv[1]), ctx);
			}
			else
			{
				asprintf(&p->data.str,
			"2exit\n, 21sh: exit: %s: numeric argument required\n", p->argv[1]);
				wrap_exit(2, ctx);
			}
			
		}
		else 
		{
			asprintf(&p->data.str, "2exit\n");
			//clear les jobs, process
			wrap_exit(EXIT_SUCCESS, ctx);// add stuff which is in ctx but not yet freed
		}
		return (0);
//	}
//	else if (p->argv[1] && !ft_isnumber(p->argv[1]))
//	{
//				asprintf(&p->data.str,
//			"21sh: exit: %s: numeric argument required\n", p->argv[1]);
//		
//	}
}
