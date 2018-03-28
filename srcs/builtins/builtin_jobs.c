/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 11:59:05 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/28 13:52:54 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int			ljob_args(t_proc *p)
{
	size_t			i;
	size_t			j;
	int				flag;
	char			*arg;

	i = 1;
	flag = 0;
	while (p->argv[i] != NULL)
	{
		arg = p->argv[i];
		if (arg[0] != '-')
			break ;
		j = 1;
		while (arg[j] != '\0')
		{
			if (arg[j] == 'l')
				flag |= BU_J_L;
			else if (arg[j] == 's')
				flag = (flag & ~BU_J_R) | BU_J_S;
			else if (arg[j] == 'r')
				flag = (flag & ~BU_J_S) | BU_J_R;
			else if (arg[j] == 'p')
				flag |= BU_J_P;
			else
			{
				ft_dprintf(STDERR_FILENO, "21sh: jobs: -%c: %s\n%s\n",
							arg[j], EOPT, BU_J_USAGE);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (flag);
}

int					ft_jobs(t_proc *p, t_ctx *ctx)
{
	int				flag;

	p->type = BU_STR;
	if ((flag = ljob_args(p)) == -1)
		return (1);
	jc_print(ctx, 1, flag);
	return (0);
}
