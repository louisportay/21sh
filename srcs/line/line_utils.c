/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 19:02:58 by lportay           #+#    #+#             */
/*   Updated: 2018/03/18 18:50:59 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

//void	join_split_lines(t_line *l)
void	join_lines(t_dlist **line, t_dlist **split_line)
{
//	t_dlist *tmp;

	if (*(char *)(*split_line)->data == '\\')
		ft_dlstremove(split_line, &delvoid);
	if (*split_line && (*line)->next)
	{
	//	tmp = *split_line;
	//	ft_dlstend(split_line);
		*line = (*line)->next;
		ft_dlstdelone(&(*line)->prev, &delvoid);
		(*line)->prev = *split_line;
		(*split_line)->next = *line;
	//	l->split_line = tmp;
	}
	else if (*split_line && !(*line)->next)
//	{
		ft_dlstdelone(line, &delvoid);
//		tmp = l->split_line;
//		ft_dlstend(&l->split_line);
//		if (*(char *)l->split_line->data == '\\')
//			ft_dlstremove(&l->split_line, &delvoid);
//		l->split_line = tmp;
//	}
//	else if (!l->split_line)
//		l->split_line = l->line;
}

//void	add_newline(t_line *l)
//{
//	if (((l->linestate->state & (SQUOTE | DQUOTE)) && !l->heredoc) ||
//(l->linestate->state & HEREDOC))
//		ft_dlstaddend(l->split_line, ft_dlstnew("\n", 1));
//}

void	toggle_emacs_mode(t_ctx *ctx, t_line *l)
{
	(void)l;
	ctx->emacs_mode = !ctx->emacs_mode;
}

