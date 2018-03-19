/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 17:38:36 by lportay           #+#    #+#             */
/*   Updated: 2018/03/14 16:07:43 by lportay          ###   ########.fr       */
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
	stack_push(&l->linestate, stack_create(UNQUOTED));
	if (l->heredoc)
		stack_push(&l->linestate, stack_create(HEREDOC));
	effective_read(ctx, l);
	if (l->split_line)
	{
		if (dlst_isblank(l->split_line->next) == false)
			add_histentry(&ctx->hist, l->split_line);
		if (!l->heredoc)
			ft_dlstaddend(l->split_line, ft_dlstnew("\n", 1));
	}
	ctx->cur_line = NULL;
	stack_del(&l->linestate);
}
