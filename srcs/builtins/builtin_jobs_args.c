/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 15:48:26 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/28 17:38:39 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int			lupdate_flag(char c, int *flag)
{
	if (c == 'l')
		*flag = (*flag & ~BU_J_P) | BU_J_L;
	else if (c == 's')
		*flag = (*flag & ~BU_J_R) | BU_J_S;
	else if (c == 'r')
		*flag = (*flag & ~BU_J_S) | BU_J_R;
	else if (c == 'p')
		*flag = (*flag & ~BU_J_L) | BU_J_P;
	else
	{
		ft_dprintf(STDERR_FILENO, "21sh: jobs: -%c: %s\n%s\n", c, EOPT,
					BU_J_USAGE);
		return (-1);
	}
	return (0);
}

int					bu_jobs_args(t_proc *p)
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
			if (lupdate_flag(arg[j], &flag) == -1)
				return (-1);
			j++;
		}
		i++;
	}
	return (flag);
}
