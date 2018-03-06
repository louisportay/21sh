/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 10:35:33 by lportay           #+#    #+#             */
/*   Updated: 2018/03/06 17:21:25 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int					ft_history(t_proc *p, t_ctx *ctx)
{

	p->type = BU_STR;
	if (p->argv[1] == NULL)
		p->data.str = dump_history(ctx->hist.list->next, -1);
	return (0);

		

}
