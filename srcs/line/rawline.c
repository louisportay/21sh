/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rawline.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lportay <lportay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 10:26:30 by lportay           #+#    #+#             */
/*   Updated: 2018/02/23 18:15:37 by lportay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Called when:
** 				-line editing mode not available (missing termcap, whatever...)
**				-When the input is not a Terminal
*/

void	getrawline(t_ctx *ctx, t_line *l)
{
	char *tmp;

	print_prompt(ctx);
	if (get_next_line(ctx->fd, &tmp) == -1)
		fatal_err(FAILREAD, ctx);
	if (!tmp && ctx->line.linestate->state == UNQUOTED)
	{
		if (ctx->fd == STDIN_FILENO)
			write(STDOUT_FILENO, "exit\n", 5);
		wrap_exit(EXIT_SUCCESS, ctx);
	}
	else if (!tmp)
		return (err_line(l, BADQUOTES));

	l->line = str_to_dlst(tmp);

	if (l->heredoc)
		query_hdocstate(l->line->next, &l->linestate, l->eohdoc);
	else
		query_linestate(l->line->next, &l->linestate);
	if (l->linestate->state != UNQUOTED)
		ft_strcpy(ctx->prompt_mode, PS2);

	join_split_lines(l);
	add_newline(l);
	free(tmp);
	l->line = NULL;
}
