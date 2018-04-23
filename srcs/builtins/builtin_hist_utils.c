/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hist_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 14:03:54 by lportay           #+#    #+#             */
/*   Updated: 2018/04/23 14:04:12 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void		print_history(t_dlist *histlist, int n, char *av)
{
	char *s;

	if (av == NULL)
		ft_putstr(s = dump_history(histlist, n));
	else
		ft_putstr(s = dump_history(histlist, ft_atoi(av)));
	free(s);
}

int			usage_history(char *av)
{
	ft_dprintf(STDERR_FILENO, "42sh: history: %s: %s\n%s",
				av, EOPT, BU_HI_USAGE);
	return (1);
}
