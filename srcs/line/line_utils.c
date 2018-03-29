/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 19:02:58 by lportay           #+#    #+#             */
/*   Updated: 2018/03/28 19:25:06 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	join_split_lines(t_line *l)
{
	t_dlist *tmp;

	if (l->split_line && l->line->next)
	{
		tmp = l->split_line;
		ft_dlstend(&l->split_line);
		if (*(char *)l->split_line->data == '\\')
			ft_dlstremove(&l->split_line, &delvoid);
		l->line = l->line->next;
		ft_dlstdelone(&l->line->prev, &delvoid);
		l->line->prev = l->split_line;
		l->split_line->next = l->line;
		l->split_line = tmp;
	}
	else if (l->split_line && !l->line->next)
	{
		ft_dlstdelone(&l->line, &delvoid);
		tmp = l->split_line;
		ft_dlstend(&l->split_line);
		if (*(char *)l->split_line->data == '\\')
			ft_dlstremove(&l->split_line, &delvoid);
		l->split_line = tmp;
	}
	else if (!l->split_line)
		l->split_line = l->line;
}

void	add_newline(t_line *l)
{
	if ((l->linestate->state & (SQUOTE | DQUOTE) && !l->eohdoc) ||
(l->linestate->state & HEREDOC))
		ft_dlstaddend(l->split_line, ft_dlstnew("\n", 1));
}

void	toggle_emacs_mode(t_ctx *ctx, t_line *l)
{
	(void)l;
	ctx->emacs_mode = !ctx->emacs_mode;
}

void	missing_quote_err(int	quote)
{
	if (quote == SQUOTE)
		ft_dprintf(STDERR_FILENO, "while looking for matching `''\n");
	else if (quote == DQUOTE)
		ft_dprintf(STDERR_FILENO, "while looking for matching `\"'\n");
}

void	warning_heredoc(t_line *l)
{
	ft_dprintf(STDERR_FILENO, "21sh: warning: here-document delimited by end-of-file (wanted `%s')\n", l->eohdoc);
	if (get_ctxaddr()->line_edition)
		ft_dlstdel(&l->line, &delvoid);
	stack_pop(&l->linestate);
}

void	err_line(t_line *l, int errno)
{
	write(STDOUT_FILENO, "\n", 1);
	dump_err(errno);
	if (errno == BADQUOTES)
		missing_quote_err(l->linestate->state);
	ft_dlstdel(&l->split_line, &delvoid);
	ft_dlstdel(&l->line, &delvoid);
	stack_push(&l->linestate, stack_create(ERROR));
}
