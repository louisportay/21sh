/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 19:02:58 by lportay           #+#    #+#             */
/*   Updated: 2018/04/10 11:24:41 by lportay          ###   ########.fr       */
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
		if (ft_dlstnewaddend(l->split_line, "\n", 1, &ft_dlstnew) == -1)
			fatal_err(NOMEM, get_ctxaddr());
}

void	missing_quote_err(int quote)
{
	if (quote == SQUOTE)
		ft_dprintf(STDERR_FILENO, "while looking for matching `''\n");
	else if (quote == DQUOTE)
		ft_dprintf(STDERR_FILENO, "while looking for matching `\"'\n");
}

void	warning_heredoc(t_line *l)
{
	ft_dprintf(STDERR_FILENO,
	"21sh: warning: here-document delimited by end-of-file (wanted `%s')\n",
	l->eohdoc);
	if (get_ctxaddr()->line_edition)
		ft_dlstdel(&l->line, &delvoid);
	else if (!l->split_line)
		if ((l->split_line = ft_dlstnew("", 0)) == NULL)
			fatal_err(NOMEM, get_ctxaddr());
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
	if (stack_create_push(&l->linestate, ERROR) == -1)
		fatal_err(NOMEM, get_ctxaddr());
}
