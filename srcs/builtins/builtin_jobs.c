/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 11:59:05 by vbastion          #+#    #+#             */
/*   Updated: 2018/03/08 15:47:44 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int					ft_jobs(t_proc *p, t_ctx *ctx)
{
	char			*str;

	p->type = BU_STR;
	if (p->argv[1] != NULL && ft_strcmp(p->argv[1], "-v") != 0)
	{
		asprintf(&str, "221sh: jobs: %s is not a valid argument\n", p->argv[1]);
		p->data.str = str;
		return (1);
	}
	jc_print(ctx, 1, p->argv[1] != NULL && ft_strcmp(p->argv[1], "-v") == 0);
	return (0);
}
