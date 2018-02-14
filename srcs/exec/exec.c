/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:30:05 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/14 17:32:45 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int						exec(t_ptok *extree)
{
	t_ctx				*ctx;
	int					ret;

	ctx = get_ctxaddr(NULL);
	if ((ret = tcsetattr(ctx->fd, TCSADRAIN, &ctx->oldtios)) != 0)
		perror("tcsetattr");
	if (extree->job != NULL)
		job_exec(extree->job, 1, get_ctxaddr(NULL));
	if ((ret = tcsetattr(ctx->fd, TCSADRAIN, &ctx->tios)) != 0)
		perror("tcsetattr reset");
	return (0);
}
