/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:30:05 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/19 14:33:01 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int						exec(t_job *extree)
{
	t_ctx				*ctx;
	int					ret;

	ctx = get_ctxaddr(NULL);
	if (ctx->istty)
	{
		if ((ret = tcsetattr(ctx->fd, TCSADRAIN, &ctx->oldtios)) != 0)
			perror("tcsetattr set");
	}
	while (extree != NULL)
	{
		job_exec(extree, 1, get_ctxaddr(NULL));
		extree = extree->next;
	}
	if (ctx->istty)
	{
		if ((ret = tcsetattr(ctx->fd, TCSADRAIN, &ctx->tios)) != 0)
			perror("tcsetattr reset");
	}
	return (0);
}
