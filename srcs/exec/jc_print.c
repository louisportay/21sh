/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jc_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbastion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:45:08 by vbastion          #+#    #+#             */
/*   Updated: 2018/02/27 17:00:22 by vbastion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

#define JC_STRRUN ("Running")
#define JC_STRSTP ("Stopped")
#define JC_STRDON ("Exit")
#define JC_STRERR ("Error")

static char				*jc_strstatus(t_job *j)
{
	int					ret;

	if ((ret = jc_status(j)) == JC_RUN)
		return (JC_STRRUN);
	else if (ret == JC_STP)
		return (JC_STRSTP);
	else if (ret == JC_DONE)
		return (JC_STRDON);
	else
		return (JC_STRERR);
}

void					jc_print(t_ctx *ctx)
{
	size_t				i;

	i = 0;
	while (i < ctx->bg_cnt)
	{
		if (ctx->bg_jobs[i] != NULL)
		{
			printf("[%lu]%-4s%-24s%s\n", i + 1,
					"",
					jc_strstatus(ctx->bg_jobs[i]),
					ctx->bg_jobs[i]->command);
		}
		i++;
	}
}
