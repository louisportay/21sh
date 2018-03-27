/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 11:59:05 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/25 20:35:01 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

#define BU_J_L 0x01
#define BU_J_S 0x02
#define BU_J_R 0x04

static int			ljob_args(t_proc *p)
{
	size_t			i;
	size_t			j;
	int				flag;

	i = 1;
	flag = 0;
	while (p->argv[i] != NULL)
	{
		if (p->argv[i][0] != '-')
			break ;
		j = 1;
		while (p->argv[i][j] != '\0')
		{
			if (p->argv[i][j] == 'l')
				flag |= BU_J_L;
			else if (p->argv[i][j] == 's')
				flag = (flag & ~BU_J_R) | BU_J_S;
			else if (p->argv[i][j] == 'r')
				flag = (flag & ~BU_J_S) | BU_J_R;
			else
			{
				/*	ERROR	*/
				return (-1);
			}
			j++;
		}
		i++;
	}
	if (p->argv[i] != NULL)
	{
		/*	ERROR	*/
		return (-1);
	}
	return (flag);
}

int					ft_jobs(t_proc *p, t_ctx *ctx)
{
	char			*str;
	int				flag;

	p->type = BU_STR;
	if ((flag = ljob_args(p)) == -1)
		return (1);
	jc_print(ctx, 1, (flag & BU_J_L) != 0);
	return (0);
}
