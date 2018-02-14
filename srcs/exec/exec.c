/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 14:30:05 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/14 20:32:00 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int						exec(t_job *extree)
{
	t_ctx				*ctx;
	int					ret;

	ctx = get_ctxaddr(NULL);
	if ((ret = tcsetattr(ctx->fd, TCSADRAIN, &ctx->oldtios)) != 0)
		perror("tcsetattr");
	while (extree != NULL)
	{
		job_exec(extree, 1, get_ctxaddr(NULL));
		extree = extree->next;
	}
	if ((ret = tcsetattr(ctx->fd, TCSADRAIN, &ctx->tios)) != 0)
		perror("tcsetattr reset");
	return (0);
}
