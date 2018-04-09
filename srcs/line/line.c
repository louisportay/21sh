/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 17:38:36 by lportay           #+#    #+#             */
/*   Updated: 2018/04/09 14:22:54 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	effective_read(t_ctx *ctx, t_line *l)
{
	if (ctx->line_edition)
	{
		lineread(ctx, l);
		while (l->linestate->state != UNQUOTED && l->linestate->state != ERROR)
			lineread(ctx, l);
	}
	else
	{
		getrawline(ctx, l);
		while (l->linestate->state != UNQUOTED && l->linestate->state != ERROR)
			getrawline(ctx, l);
	}
}

void		ft_readline(t_ctx *ctx, t_line *l, char *prompt_mode)
{
	l->split_line = NULL;
	ctx->cur_line = l;
	ft_strcpy(ctx->prompt_mode, prompt_mode);
	if (stack_create_push(&l->linestate, UNQUOTED) == -1)
		fatal_err(NOMEM, get_ctxaddr());
	if (l->eohdoc)
		if (stack_create_push(&l->linestate, HEREDOC) == -1)
			fatal_err(NOMEM, get_ctxaddr());
	effective_read(ctx, l);
	if (l->split_line)
	{
		if (dlst_isblank(l->split_line->next) == false)
			add_histentry(&ctx->hist, l->split_line);
		if (!l->eohdoc)
			if (ft_dlstnewaddend(l->split_line, "\n", 1 ,& ft_dlstnew) == -1)
				fatal_err(NOMEM, ctx);
	}
	ctx->cur_line = NULL;
	stack_del(&l->linestate);
}
